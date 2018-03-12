#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
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


    char* buffer = malloc(sizeof(char) * 3000);
    buffer[0] = 0;
    struct CSVFile file = *(struct CSVFile*)files.val;
    do {
        struct Node* list = NULL;
        int uniqueCount = 0;
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
        char* buf2 = malloc(sizeof(char)*200);
        sprintf(buf2, "File %s has %d unique strings\n", file.fileName, uniqueCount);
        strcat(buffer, buf2);
        //free(buf2);
        linkedlist_destroy(list);
    } while (1);

	// add name to printout

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	double result = ((stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3) / 1e6;
	printf("=== T1 completed ===\n");
    printf("=== T1 report start ===\n");
    printf("%s", buffer);

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
in each file, exclude pure numbers (either integer or floating-point values) */

    loadFiles();
    struct Node filesOG = files;

    struct CSVFile file = *(struct CSVFile*)files.val;
    struct Node* list = NULL;
    int max = 0;
    int min = 100000;
    int count = 0;
    int sum = 0;
    double avg;
    do {
        for (int i = 0; i < file.len; i++) {
            struct CSVLine line = file.lines[i];
            for (int j = 0; j < line.len; j++) {
                struct CSVCell cell = line.line[j];
                if (cell.isAlphanumeric) {
                    int num = strlen(cell.data);
                    if (num > max) {
                        max = num;
                    } else if (num < min) {
                        min = num;
                    }

                    sum += num;
                    count++;
                }
            }
        }
        if (files.next != NULL) {
            files = *files.next;
            file = *(struct CSVFile*)files.val;
        } else {
            break;
        }
    } while (1);

    // reset file pointer
    files = filesOG;
    avg = ((double)sum/(double)count);

    double variance = 0;
    do {
        for (int i = 0; i < file.len; i++) {
            struct CSVLine line = file.lines[i];
            for (int j = 0; j < line.len; j++) {
                struct CSVCell cell = line.line[j];
                if (cell.isAlphanumeric) {
                    int num = strlen(cell.data);
                    variance += (avg - num) * (avg - num);
                }
            }
        }
        if (files.next != NULL) {
            files = *files.next;
            file = *(struct CSVFile*)files.val;
        } else {
            break;
        }
    } while (1);

    variance /= count;

    linkedlist_destroy(list);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	double result = ((stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3) / 1e6;
	printf("=== T2 completed ===\n");
	printf("=== T2 report start ===\n");
    printf("Max: %d, Min: %d, Avg: %f, Var %f", max, min, avg, variance);
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

    char* buffer = malloc(sizeof(char) * 3000);
    buffer[0] = "0";

	int rowCount = 0;
	int fileTotal = 0;
	int columnCount = 0;

    loadFiles();
    struct Node filesOG = files;

    struct CSVFile file = *(struct CSVFile*)files.val;

    do {
        int localColMax = 0;
        int localRowMax = 0;
        int cellCount = 0;
        int missingOrZeroCount = 0;
        for (int i = 0; i < file.len; i++) {
            struct CSVLine line = file.lines[i];
            columnCount += line.len;

            if (localColMax < line.len) {
                localColMax = line.len;
            }

            rowCount++;
            for (int j = 0; j < line.len; j++) {
                struct CSVCell cell = line.line[j];
                if (cell.isEmpty) {
                    missingOrZeroCount++;
                } else if (cell.isNumeric) {
                    if (IsValidNumber(cell.data)) {
                        double val = atof(cell.data);
                        if (val == 0) {
                            missingOrZeroCount++;
                        }
                    }
                }
                cellCount++;
            }
        }

        char* buf2 = malloc(sizeof(char)*200);
        sprintf(buf2, "File %s has %d rows, %f columns, and a ratio of %f empty cells\n", file.fileName, rowCount,
                (double)columnCount / (double)rowCount, (double)missingOrZeroCount/(double)cellCount);

        fileTotal++;
        if (files.next != NULL) {
            files = *files.next;
            file = *(struct CSVFile*)files.val;
        } else {
            break;
        }
    } while (1);

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

