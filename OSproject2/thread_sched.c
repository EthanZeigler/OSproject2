#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include "thread_tasks.h"
#include "thread_sched.h"
#include "linkedlist.h"
#include "csvparser.h"

#define NUM_THREADS 3
#define NUM_TO_RUN	100000


int i, policy, errcode;
int params[NUM_THREADS];
pthread_t tid[NUM_THREADS];
pthread_attr_t attr;
struct sched_param schedparam;
char g_argc;
char **g_argv;
int prio = 0;




int main(int argc, char **argv){
    loadFiles();

	g_argc = (char) malloc(1000);
	g_argv = (char**) malloc(1000);
	g_argv = argv;
	get_default_attr();
	switch(thread_count()){
		case 'M':
			if(argc < 3){
				create_taskone_thread(prio);
				create_tasktwo_thread(prio);
				create_taskthree_thread(prio);
				//get_each_sched_policy();
				terminate_threads();
				return 0;
			}
			else if(strcmp(argv[2], "sched") == 0){
				set_schedule_policy();
				create_taskone_thread(prio);
				create_tasktwo_thread(prio);
				create_taskthree_thread(prio);
				//get_each_sched_policy();
				terminate_threads();
				return 0;
			}
			else if(strcmp(argv[2], "priority") == 0){
				if(strcmp(argv[4], "low") == 0){
					switch(atoi(argv[3])){
						case 1 :
							create_taskone_thread(-1);
							create_tasktwo_thread(prio);
							create_taskthree_thread(prio);
							break;
						case 2 :
							create_taskone_thread(prio);
							create_tasktwo_thread(-1);
							create_taskthree_thread(prio);
							break;
						case 3 :
							create_taskone_thread(prio);
							create_tasktwo_thread(prio);
							create_taskthree_thread(-1);
							break;
					}
					//get_each_sched_policy();
					terminate_threads();
					return 0;
				}
				else if(strcmp(argv[4], "high") == 0){
					switch(atoi(argv[3])){
						case 1 :
							create_taskone_thread(3);
							create_tasktwo_thread(prio);
							create_taskthree_thread(prio);
							break;
						case 2 :
							create_taskone_thread(prio);
							create_tasktwo_thread(3);
							create_taskthree_thread(prio);
							break;
						case 3 :
							create_taskone_thread(prio);
							create_tasktwo_thread(prio);
							create_taskthree_thread(3);
							break;
					}
					//get_each_sched_policy();
					terminate_threads();
					return 0;
				}
			}
		case 'S':
			switch(atoi(argv[2])){
				case 1 :
				create_taskone_thread(prio);
				//get_single_sched_policy(0);
				terminate_thread(0);
				return 0;
				case 2 :
				create_tasktwo_thread(prio);
				//get_single_sched_policy(1);
				terminate_thread(1);
				return 0;
				case 3 :
				create_taskthree_thread(prio);
				//get_single_sched_policy(2);
				terminate_thread(2);
				return 0;
			}
		default:break;
	}

    return 0;
}
	/* get the default attributes */
void get_default_attr(void){
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
}

void set_schedule_policy(void){
	if(strcmp(g_argv[3], "RR") == 0)
		pthread_attr_setschedpolicy(&attr, SCHED_RR);
	else if(strcmp(g_argv[3], "FIFO") == 0)
		pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	else pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
}


/* we give different priority to different thread, [1..99]; larger = higher */
void create_taskone_thread(int myprio){
		myprio = (myprio + 1) * 5;
		schedparam.sched_priority = myprio;
		assert(sched_get_priority_min(2) <= myprio && sched_get_priority_max(2) >= myprio);
		if ((errcode = pthread_attr_setschedparam(&attr, &schedparam)) != 0)
		{
			fprintf(stderr, "Error setting priority: ");
			switch (errcode)
			{
				case EINVAL:
					fprintf(stderr, "EINVAL\n"); break;
				case ENOTSUP:
					fprintf(stderr, "ENOTSUP\n"); break;
			};
		}
		/* parameter to hold thread ID */
		params[0] = 0;
		/* create thread */
		if ((errcode = pthread_create(&tid[0], &attr, taskone, &(params[0]))) != 0) 
		{
			fprintf(stderr, "Error creating thread: ");
			switch (errcode)
			{
				case EAGAIN: 
					fprintf(stderr, "EAGAIN\n"); break;
				case EINVAL:
					fprintf(stderr, "EINVAL\n"); break;
				case EPERM:
					fprintf(stderr, "EPERM\n"); break;
			};
		} 
		else 
		{
			//printf("Thread #%d created with priority %d.\n", 0, myprio);
		}
}
	/* we give different priority to different thread, [1..99]; larger = higher */
void create_tasktwo_thread(int myprio){
	myprio = (myprio + 1) * 5;
	schedparam.sched_priority = myprio;
		assert(sched_get_priority_min(2) <= myprio && sched_get_priority_max(2) >= myprio);
	if ((errcode = pthread_attr_setschedparam(&attr, &schedparam)) != 0)
	{
		fprintf(stderr, "Error setting priority: ");
		switch (errcode)
		{
			case EINVAL:
				fprintf(stderr, "EINVAL\n"); break;
			case ENOTSUP:
				fprintf(stderr, "ENOTSUP\n"); break;
		};
	}
	/* parameter to hold thread ID */
	params[1] = 1;
	/* create thread */
	if ((errcode = pthread_create(&tid[1], &attr, tasktwo, &(params[1]))) != 0) 
	{
		fprintf(stderr, "Error creating thread: ");
		switch (errcode)
		{
			case EAGAIN: 
				fprintf(stderr, "EAGAIN\n"); break;
			case EINVAL:
				fprintf(stderr, "EINVAL\n"); break;
			case EPERM:
				fprintf(stderr, "EPERM\n"); break;
		};
	} 
	else 
	{
		//printf("Thread #%d created with priority %d.\n", 1, myprio);
	}
}

void create_taskthree_thread(int myprio){
	myprio = (myprio + 1) * 5;
	schedparam.sched_priority = myprio;
	assert(sched_get_priority_min(2) <= myprio && sched_get_priority_max(2) >= myprio);
	if ((errcode = pthread_attr_setschedparam(&attr, &schedparam)) != 0)
	{
		fprintf(stderr, "Error setting priority: ");
		switch (errcode)
		{
			case EINVAL:
				fprintf(stderr, "EINVAL\n"); break;
			case ENOTSUP:
				fprintf(stderr, "ENOTSUP\n"); break;
		};
	}
	/* parameter to hold thread ID */
	params[2] = 2;
	/* create thread */
	if ((errcode = pthread_create(&tid[2], &attr, taskthree, &(params[2]))) != 0) 
	{
		fprintf(stderr, "Error creating thread: ");
		switch (errcode)
		{
			case EAGAIN: 
				fprintf(stderr, "EAGAIN\n"); break;
			case EINVAL:
				fprintf(stderr, "EINVAL\n"); break;
			case EPERM:
				fprintf(stderr, "EPERM\n"); break;
		};
	} 
	else 
	{
		//printf("Thread #%d created with priority %d.\n", 2, myprio);
	}
}
	/* get each thread's scheduling policy */
void get_each_sched_policy(void){
	int get_policy[NUM_THREADS];
	struct sched_param get_param;
	sleep(2);
	printf("Reading policy from threads...\n");
	for (i = 0; i < NUM_THREADS; i++){
		pthread_getschedparam(tid[i], &get_policy[i], &get_param);
		printf("Thread #%d: ", i);
		if (get_policy[i] == SCHED_OTHER)
			printf("SCHED_OTHER\n");
		else if (get_policy[i] == SCHED_RR)
			printf("SCHED_RR\n");
		else if (get_policy[i] == SCHED_FIFO)
			printf("SCHED_FIFO\n");
	}
}

void get_single_sched_policy(int id){
	int get_policy[NUM_THREADS];
	struct sched_param get_param;
	sleep(2);
	printf("Reading policy from thread...\n");
	pthread_getschedparam(tid[id], &get_policy[id], &get_param);
	printf("Thread #%d: ", id);
	if (get_policy[id] == SCHED_OTHER)
		printf("SCHED_OTHER\n");
	else if (get_policy[id] == SCHED_RR)
		printf("SCHED_RR\n");
	else if (get_policy[id] == SCHED_FIFO)
		printf("SCHED_FIFO\n");
}

void terminate_threads(void){
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}
}

void terminate_thread(int id){
	pthread_join(tid[id], NULL);
}

char thread_count(){
	if(strcmp(g_argv[1], "multi") == 0){
		return 'M';
	}
	else return 'S';
}

