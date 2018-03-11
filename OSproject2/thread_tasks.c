#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <libnet.h>
#include "csvparser.h"
#include "linkedlist.h"
#include "thread_tasks.h"

#define NUM_TO_RUN	100000

struct timespec start, stop;

struct Node files;

void *taskone (void *param)
{
	//file = readFile()
	int tid = *((int*)param);
	int total_primes = 0;

	//printf("Thread #%d executing task 1.\n", tid);
	
	/* wait 2 seconds for fair start and pretty-printing */
	sleep(2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	/*  Find total number of unique words among all non-numeric string literals in each file */
	loadFiles();

	struct Node* list = NULL;
	int uniqueCount = 0;

    struct CSVFile file = *(struct CSVFile*)files.val;
    do {
        for (int i = 0; i < file.len; i++) {
            struct CSVLine line = file.lines[i];
            for (int j = 0; j < line.len; j++) {
                struct CSVCell cell = line.line[j];
                if (cell.isAlphanumeric) {
                    if (!linkedlist_contains_str(list, cell.data)) {
                        uniqueCount++;
                        linkedlist_append_char(list, cell.data);
                    }
                }
            }
        }
        if (files.next != NULL) {
            files = *files.next;
        } else {
            break;
        }
    } while (1);
	linkedlist_destroy(list);

	// add name to printout

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	double result = ((stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3) / 1e6;
	printf("=== T1 completed ===\n");
	printf("=== T1 report start ===\n");

/* iterate through files and print results */

	printf("T1 RESULT: Total elapsed time : %f seconds\n", result);
	printf("=== T1 report end ===\n");

	pthread_exit(0);
}

void *tasktwo (void *param)
{
	int tid = *((int*)param);
	int total_primes = 0;

	//printf("Thread #%d executing task 2.\n", tid);
	
	/* wait 2 seconds for fair start and pretty-printing */
	sleep(2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	/*  Find maximum, minimum, average, and variance of lengths of alphanumeric strings
in each file, exclude pure numbers (either integer or floating-point values) */struct Node* list = NULL;
    int max = 0;
    int min = 100000;
    int count = 0;
    int sum = 0;

    struct CSVFile file = *(struct CSVFile*)files.val;
    do {
        for (int i = 0; i < file.len; i++) {
            struct CSVLine line = file.lines[i];
            for (int j = 0; j < line.len; j++) {
                struct CSVCell cell = line.line[j];
                if (cell.isAlphanumeric) {
                    // is a number, continue
                }
            }
        }
        if (files.next != NULL) {
            files = *files.next;
        } else {
            break;
        }
    } while (1);
    linkedlist_destroy(list);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	double result = ((stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3) / 1e6;
	printf("=== T2 completed ===\n");
	printf("=== T2 report start ===\n");

	/* iterate through files and print results */

	printf("T2 RESULT: Total elapsed time : %f seconds\n", result);
	printf("=== T2 report end ===\n");

	pthread_exit(0);
}

void *taskthree (void *param)
{
	int tid = *((int*)param);
	int total_primes = 0;

	//printf("Thread #%d executing task 3.\n", tid);
	
	/* wait 2 seconds for fair start and pretty-printing */
	sleep(2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	/*  Count ratio of missing or zero values in each file. Also, find maximum, minimum,
average of the numbers of rows and columns of all files. */


	int cellCount = 0;
	int missingOrZeroCount = 0;
	int rowCount = 0;
	int rowTotal = 0;
	int columnCount = 0;
	int columnTotal = 0;


	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	double result = ((stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3) / 1e6;
	printf("=== T3 completed ===\n");
	printf("=== T3 report start ===\n");

	/* iterate through files and print results */

	printf("T3 RESULT: Total elapsed time : %f seconds\n", result);
	printf("=== T3 report end ===\n");

	pthread_exit(0);
}

void getFiles()
{
	char* path = malloc(sizeof(char) * 300);
	getcwd(path, sizeof(path));
	strcat(path, "analcatdata/");

	struct dirent *entry;
	DIR *dir = opendir(path);
	if (dir == NULL) {
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		printf("%s\n",entry->d_name);
	}

	closedir(dir);
}

void loadFiles() {
    DIR *dp;
    struct dirent *ep;

    //char* dir = "./analcatdata/";
    char* dir = "/Users/Ethan/CLionProjects/OSproject2/OSproject2/analcatdata/";
    dp = opendir(dir);
    linkedlist_init(&files);
    if (dp != NULL) {
        while (ep = readdir (dp)){
            if (strcmp(ep->d_name, ".") && strcmp(ep->d_name, "..") && strcmp(ep->d_name, "README")) {
                char* loc = strdup(dir);
                strcat(loc, ep->d_name);
                FILE* file = fopen(loc, "r");
                struct CSVFile csv = readFile(file, ep->d_name);
                linkedlist_append(&files, &csv);
            }
        }
        (void) closedir (dp);
    }
    else
        perror ("Couldn't open the directory");
}