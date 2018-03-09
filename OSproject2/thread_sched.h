#ifndef PROJECT2_THREADSCHED_H
#define PROJECT2_THREADSCHED_H


extern void set_schedule_policy(void);
extern void create_taskone_thread(int myprio);
extern void create_tasktwo_thread(int myprio);
extern void create_taskthree_thread(int myprio);
extern void get_sched_policy(void);
extern void get_each_sched_policy(void);
extern void terminate_threads(void);
extern void get_default_attr(void);
extern void get_single_sched_policy(int id);
extern void terminate_thread(int id);
extern char thread_count();

#endif