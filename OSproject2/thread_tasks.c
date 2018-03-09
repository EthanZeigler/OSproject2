#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define NUM_TO_RUN	100000

struct timespec start, stop;

void *taskone (void *param)
{
	int tid = *((int*)param);
	int total_primes = 0;

	//printf("Thread #%d executing task 1.\n", tid);
	
	/* wait 2 seconds for fair start and pretty-printing */
	sleep(2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	/*  Find total number of unique words among all non-numeric string literals in each file */
	for (int i = 2; i < NUM_TO_RUN; ++i) {
		short isprime = 1;
		for (int j = 1; j < i; ++j) {
			if (i % j == 0 && j > 1) {
				isprime = 0;
				break;
			}
		}
		if (isprime > 0) {
			++total_primes;
		}
	}

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
in each file, exclude pure numbers (either integer or floating-point values) */
	for (int i = 2; i < NUM_TO_RUN; ++i) {
		short isprime = 1;
		for (int j = 1; j < i; ++j) {
			if (i % j == 0 && j > 1) {
				isprime = 0;
				break;
			}
		}
		if (isprime > 0) {
			++total_primes;
		}
	}

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
	for (int i = 2; i < NUM_TO_RUN; ++i) {
		short isprime = 1;
		for (int j = 1; j < i; ++j) {
			if (i % j == 0 && j > 1) {
				isprime = 0;
				break;
			}
		}
		if (isprime > 0) {
			++total_primes;
		}
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	double result = ((stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3) / 1e6;
	printf("=== T3 completed ===\n");
	printf("=== T3 report start ===\n");

	/* iterate through files and print results */

	printf("T3 RESULT: Total elapsed time : %f seconds\n", result);
	printf("=== T3 report end ===\n");

	pthread_exit(0);
}