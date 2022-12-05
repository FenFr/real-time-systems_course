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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//////////////////////////////////////////////////////////////////////////////
void* print_hello_function( void *ptr );
void* print_world_function( void *ptr );

pthread_mutex_t 	mutex;
pthread_cond_t		cond_hello_printed;
int                 var_hello_printed = 0;

//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	pthread_attr_t 	attr;
	pthread_t 		thread1, thread2;
	char 			*message1 = "Hello\n";
	char 			*message2 = "World!\n";
	
	pthread_mutexattr_t	mutex_attr;

	pthread_mutexattr_init(&mutex_attr);
	pthread_mutex_init(&mutex, &mutex_attr);
	pthread_cond_init(&cond_hello_printed, NULL);
	
	pthread_attr_init(&attr);
	pthread_create(&thread1, &attr, print_hello_function, (void*) message1);
	pthread_create(&thread2, &attr, print_world_function, (void*) message2);
	
	printf("I have just created two threads.\n");
	
	pthread_join(thread1, 0);
	pthread_join(thread2, 0);
	
	pthread_cond_destroy(&cond_hello_printed);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
void* print_hello_function( void *ptr )
{
	pthread_mutex_lock(&mutex);

	char *message;
	message = (char *) ptr;
	printf("%s", message);
	
	var_hello_printed = 1;
	pthread_cond_signal(&cond_hello_printed);
	
	pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

void* print_world_function( void *ptr )
{
	pthread_mutex_lock(&mutex);

	while (var_hello_printed == 0)
		pthread_cond_wait(&cond_hello_printed, &mutex);

	char *message;
	message = (char *) ptr;
	printf("%s", message);
	
	pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}
