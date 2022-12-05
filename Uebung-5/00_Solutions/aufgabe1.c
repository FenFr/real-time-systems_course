//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		5
// Task:          		1
// Name:          		aufgabe1.c
// Description:   		Thread creation
// Compiler call:		cc -o aufgabe1 aufgabe1.c -lpthread
//////////////////////////////////////////////////////////////////////////////
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//////////////////////////////////////////////////////////////////////////////
void* thread_start(void *ptr);

//////////////////////////////////////////////////////////////////////////////
int main(void)
{	pthread_attr_t 	attr;
	pthread_t 		thread;

	pthread_attr_init(&attr);
	pthread_create(&thread, &attr, thread_start, 0);
	printf("I have just created a thread.\n");
	pthread_join(thread, 0);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
void* thread_start( void *ptr )
{
	printf("Hello World!\n");
	pthread_exit(0);
}
