//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		5
// Task:          		2
// Name:          		aufgabe2.c
// Description:   		Creating multiple threads
// Compiler call:		cc -o aufgabe2 aufgabe2.c -lpthread
//////////////////////////////////////////////////////////////////////////////
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>	// pthread_*
#include <sched.h>		// cpu_set_t , CPU_SET
#include <string.h>		// strcat

#include <sys/resource.h>	// needed for getpriority() / setpriority()
							// -> nice() value of non-RT processes/threads

#include <sys/syscall.h> /* For SYS_xxx definitions */

//////////////////////////////////////////////////////////////////////////////
void* print_message_function( void *ptr );
void set_cpu_affinity();

struct thread_arg {
	int	thread_prio;	// nice value
	char 	*message;
};

//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	int status;

	pthread_attr_t 	attr1;
	pthread_attr_t 	attr2;

	pthread_t 		thread1;
	pthread_t 		thread2;

	char 			*message1 = "Hello\n";
	char 			*message2 = "World!\n";

	set_cpu_affinity(); // bind to CPU core 0

	// main thread params
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
	printf("Main thread: pid = %d, tid = %d \n", pid, tid);

	// init son thread attribute structures
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	// create thread function arguments
	struct thread_arg arg1;
//	arg1.thread_prio = -20;	// negative nice values (-20 ... -1) need root privileges!
	arg1.thread_prio = 0;	// highest non-root prio = default nice value of 0
//	arg1.thread_prio = 19;	// lowest ("nicest") non-root prio
	arg1.message = message1;

	struct thread_arg arg2;
//	arg2.thread_prio = -20; // negative nice values (-20 ... -1) need root privileges!
//	arg2.thread_prio = 0;	// highest non-root prio = default nice value of 0
	arg2.thread_prio = 19;	// lowest ("nicest") non-root prio
	arg2.message = message2;

	// create son threads -> son1, son2
	status = pthread_create(&thread1, &attr1, print_message_function, (void*) &arg1);
	printf("Status pthread_create: %d\n", status);
	status = pthread_create(&thread2, &attr2, print_message_function, (void*) &arg2);
	printf("Status pthread_create: %d\n", status);

	printf("I have just created two threads.\n");

	// join son threads
	pthread_join(thread1, 0);
	pthread_join(thread2, 0);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
void* print_message_function( void *ptr )
{
	set_cpu_affinity(); // bind to CPU core 0

	struct thread_arg *arg = (struct thread_arg *) ptr;

	// apply thread nice value
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
	int ret = setpriority(PRIO_PROCESS, tid, arg->thread_prio);
	printf("Status setpriority: %d \n", ret);
	printf("Son thread: pid = %d, tid = %d, prio = %d \n", pid, tid, getpriority(PRIO_PROCESS,tid));

	int j;
	for (j=0; j<10000000; j++) {;} // busy wait

	// print message
	char *message;
	message = (char *) arg->message;
	printf("%s", message);

    pthread_exit(0);
}

//////////////////////////////////////////////////////////////////////////////
void set_cpu_affinity()
{
	// we can set one or more bits here, each one representing a single CPU
	cpu_set_t cpuset; 

	// the CPU we want to use (core 0)
	int cpu = 1;

	CPU_ZERO(&cpuset);	// clears the cpuset
	CPU_SET(cpu, &cpuset);	// set CPU 0 on cpuset

	/*
	* cpu affinity for the calling thread 
	* first parameter is the pid, 0 = calling thread
	* second parameter is the size of your cpuset
	* third param is the cpuset in which your thread will be
	* placed. Each bit represents a CPU
	*/
	sched_setaffinity(0, sizeof(cpuset), &cpuset);
	//pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
}

