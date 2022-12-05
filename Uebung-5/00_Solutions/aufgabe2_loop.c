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
void* print_message_function( void *ptr );

//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	pthread_attr_t 	attr;
	pthread_t 		thread1, thread2;
	char 			*message1 = "I am thread 1 and have to print 'Hello'\n";
	char 			*message2 = "I am thread 2 and have to print 'World!'\n";

	pthread_attr_init(&attr);
	pthread_create(&thread1, &attr, print_message_function, (void*) message1);
	pthread_create(&thread2, &attr, print_message_function, (void*) message2);
	printf("I have just created two threads.\n");
	pthread_join(thread1, 0);
	pthread_join(thread2, 0);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
void* print_message_function( void *ptr )
{
	int i;
	for (i=0; i<10000; i++) {
		char *message;
		message = (char *) ptr;
		printf("%s", message);
	}
    pthread_exit(0);
}
