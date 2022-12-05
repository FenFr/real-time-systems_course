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

//////////////////////////////////////////////////////////////////////////////
void* print_message_function( void *ptr );
void set_cpu_affinity();

//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	int status;

	struct sched_param	my_param;	// father sched param
	int					my_policy;	// father default sched policy

	int 				sch_policy;	// desired sched policy

	struct sched_param	sch_param1;	// son 1 sched param
	struct sched_param	sch_param2;	// son 2 sched param

	pthread_attr_t 		attr1;
	pthread_attr_t 		attr2;

	pthread_t 			thread1;
	pthread_t 			thread2;

	char 				*message1 = "Hello\n";
	char 				*message2 = "World!\n";

	set_cpu_affinity(); // bind to CPU core 0

	// define sched policy to be used in main and son threads

//	sch_policy = SCHED_OTHER;	// non-realtime, CFS -> RT prio range is always (0 ... 0) and only nice values can be specified (19 .. 0 .. -20)
	sch_policy = SCHED_FIFO;	// real-time, prio-based -> threads of equal RT prio are completed in FIFO fashion
//	sch_policy = SCHED_RR;		// real-time, prio-based -> time slicing between equal RT priority threads

	printf("New Sched Policy To Be Used: %d\n", sch_policy);
	printf("Sched Policy Prio Range: %d - %d\n", sched_get_priority_min(sch_policy), sched_get_priority_max(sch_policy));


	// modify father thread's scheduling parameters ...

	pthread_getschedparam(pthread_self(), &my_policy, &my_param);
	printf("Father Thread Default Sched Policy: %d\n", my_policy);
	printf("Father Thread Default Sched Prio: %d\n", my_param.sched_priority);
	printf("Default Sched Policy Prio Range: %d - %d\n", sched_get_priority_min(my_policy), sched_get_priority_max(my_policy));

	// set sched policy and prio for father

	my_param.sched_priority = sched_get_priority_min(sch_policy)+2;		// set min prio + 2 for father
//	my_param.sched_priority = sched_get_priority_max(sch_policy);		// set max prio for father
	printf("Set New Father Thread Sched Prio: %d\n", my_param.sched_priority);
	status = pthread_setschedparam(pthread_self(), sch_policy, &my_param);
	printf("Status pthread_setschedparam: %d\n", status);

	pthread_getschedparam(pthread_self(), &my_policy, &my_param);
	printf("New Father Thread Sched Policy: %d\n", my_policy);
	printf("New Father Thread Sched Prio: %d\n", my_param.sched_priority);


	// create son threads with modified scheduling parameters (attribute structure) ...

	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	// set sched policy for sons

	status = pthread_attr_setschedpolicy(&attr1, sch_policy);
	printf("Status pthread_attr_setschedpolicy: %d\n", status);
	status = pthread_attr_setschedpolicy(&attr2, sch_policy);
	printf("Status pthread_attr_setschedpolicy: %d\n", status);

	// set sched prio for sons (prio must be <= father thread prio)

	pthread_attr_getschedparam(&attr1, &sch_param1);
	printf("Son 1 Thread Default Sched Prio: %d\n", sch_param1.sched_priority);
	pthread_attr_getschedparam(&attr2, &sch_param2);
	printf("Son 2 Thread Default Sched Prio: %d\n", sch_param2.sched_priority);

//	sch_param1.sched_priority = sched_get_priority_min(sch_policy);		// set min prio for 1st son (Hello)
	sch_param1.sched_priority = sched_get_priority_min(sch_policy)+1;	// set min prio + 1 for 1st son (Hello)
	printf("Set New Son Thread 1 Sched Prio: %d\n", sch_param1.sched_priority);

	sch_param2.sched_priority = sched_get_priority_min(sch_policy);		// set min prio for 2nd son (World)
//	sch_param2.sched_priority = sched_get_priority_min(sch_policy)+1;	// set min prio + 1 for 2nd son (World)
	printf("Set New Son Thread 2 Sched Prio: %d\n", sch_param2.sched_priority);

	status = pthread_attr_setschedparam(&attr1, &sch_param1);
	printf("Status pthread_attr_setschedparam: %d\n", status);
	status = pthread_attr_setschedparam(&attr2, &sch_param2);
	printf("Status pthread_attr_setschedparam: %d\n", status);


	// set attribute flag needed for new sched params to have effect in pthread_create()
	// -> otherwise PTHREAD_INHERIT_SCHED is used that lets children inherit sched params of parent
	pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);


	// create son threads -> son1, son2
	status = pthread_create(&thread1, &attr1, print_message_function, (void*) message1);
	printf("Status pthread_create: %d\n", status);
	status = pthread_create(&thread2, &attr2, print_message_function, (void*) message2);
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

/*
	// check thread sched policy and prio
	struct sched_param	param;	// sched param
	int					policy;	// sched policy
	pthread_getschedparam(pthread_self(), &policy, &param);
	printf("Thread Sched Policy: %d\n", policy);
	printf("Thread Sched Prio: %d\n", param.sched_priority);
*/

/*
	// the loops are just for demonstrating FIFO vs RR
	int i;
	for (i=0; i<20; i++) {
		printf("%d: ", i);
*/
		int j;
		for (j=0; j<10000000; j++) {;} // busy wait

		// print message
		char *message;
		message = (char *) ptr;
		printf("%s", message);
/*
	}
*/

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

