//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		6
// Task:          		4
// Name:          		aufgabe4.c
// Description:   		Concurrent access to a resctrictive region
//						(10 instances at once) with a max. of 50
//						possible threads. Thread IDs in the region
//						are printed. Press <1>+<ENTER> to quit. Access
//						control is handled by one counting semaphore.
// Compiler call:		cc -o aufgabe4 aufgabe4.c -lpthread
//////////////////////////////////////////////////////////////////////////////
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <limits.h>
#include <sched.h>

//////////////////////////////////////////////////////////////////////////////
#define MAX_THREADS			50				
#define MAX_REGION_ENTRIES	10

void* thread_function(void *ptr);
void enter_region(size_t id);
void leave_region(size_t id);

int				cancel_threads = 0;
sem_t			region_semaphore;
pthread_mutex_t	region_mutex = PTHREAD_MUTEX_INITIALIZER;
size_t			regionentries[MAX_REGION_ENTRIES];

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{	pthread_attr_t	attr;
	pthread_t 		threads[MAX_THREADS];
	size_t			i, counter = 0;

	// 0=local process, MAX_REGION_ENTRIES=initial state
	if ( sem_init( &region_semaphore, 0, MAX_REGION_ENTRIES ) == 0 )
	{	if ( pthread_attr_init( &attr ) == 0 )
		{	for (i=0; i<MAX_THREADS; i++)
			{
				if ( pthread_create( &(threads[counter]), &attr, thread_function, (void*)i+1) == 0 )
					counter++;
			}
			scanf("%d", &cancel_threads);	// set cancel condition
			for (i=0;i<counter;i++)
			{
				pthread_join( threads[i], 0);
			}
		}
		sem_destroy( &region_semaphore);
	}
	printf("Main thread finished!\n");
}

//////////////////////////////////////////////////////////////////////////////
void* thread_function(void *ptr)
{
	size_t threadid=(size_t)ptr;
	time_t	t;

	while( ! cancel_threads )			// check cancel condition
	{
		enter_region(threadid);			// enter restrictive region
		t=time(0);                  	// short wait (passive)
		usleep((localtime(&t)->tm_sec+localtime(&t)->tm_min)*1000 );
		leave_region(threadid);			// leave restrictive region
		sched_yield();					// yield CPU
	}
	printf("Thread %zu finished!\n", threadid);
	return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Critical section to regionentries[] already locked!
void print_region_entries()
{
	int	i;
	printf("Threads in region: ");
	for (i=0; i<MAX_REGION_ENTRIES; i++)
		printf("%zu ", regionentries[i]);
	printf("\n");

	for(i=0;i<1000000;i++)				// short wait (active)
		i;
}


//////////////////////////////////////////////////////////////////////////////
// Entering of restrictive region
// If not possible, thread is blocked
void enter_region(size_t id)
{
	int	i;
	sem_wait( &region_semaphore );

	// ----> only for demonstration
	// Enter critical section to determine
	// and print IDs of threads that are currently
	// within the restrictive region
	pthread_mutex_lock(&region_mutex);
	for (i=0;i<MAX_REGION_ENTRIES;i++)
	{
		if ( regionentries[i]==0 )
		{	regionentries[i]=id;
			break;
		}
	}
	print_region_entries();
	pthread_mutex_unlock(&region_mutex); // Leave critical section
	// <--- only for demonstration
}


//////////////////////////////////////////////////////////////////////////////
// Leaving of restrictive region
// Must have been entered successfully before
void leave_region(size_t id)
{
	int	i;

	// ----> only for demonstration
	pthread_mutex_lock(&region_mutex);
	for (i=0;i<MAX_REGION_ENTRIES;i++)
	{	if ( regionentries[i]==id )
		{	regionentries[i]=0;
			break;
		}
	}
	print_region_entries();
	pthread_mutex_unlock(&region_mutex);
	// <--- only for demonstration

	sem_post( &region_semaphore );
}
