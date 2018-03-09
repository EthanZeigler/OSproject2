#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>
#include <sched.h>
#include <string.h>
#include "thread_tasks.h"
#include "thread_sched.h"
#define NUM_THREADS 3 
#define NUM_TO_RUN	100000

int main(int argc, char **argv){
    get_default_attr();
    set_schedule_policy(argv[3]);
    create_taskone_thread();
    create_tasktwo_thread();
    create_taskthree_thread();
    get_sched_policy();
    get_each_sched_policy();
    terminate_threads();
    return 0;
}