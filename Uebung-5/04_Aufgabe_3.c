//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Co-Author			Fenya Freitag
// Exercise:      		5
// Task:          		3
// Name:          		04_Aufgabe_3.c
// Description:   		?
// Compiler call:		cc -o aufgabe3 aufgabe3.c -lpthread
//////////////////////////////////////////////////////////////////////////////


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT	300000


void* 	threadcode(void *ptr);

int 	rec(int number);


// MAIN //////////////////////////////////////////////////////////////////////

int main(void) {

	int				number;
	pthread_attr_t 	attr;
	pthread_t 		thread1;

	pthread_attr_init(&attr);
	pthread_create(&thread1, &attr, threadcode, 0);
	pthread_join(thread1,0);

	return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////


void* threadcode(void *ptr)
{	printf("\nResult is: %d.\n", rec(0));
	return 0;
}


int rec(int number)
{	if (!(number%200))
		printf("\n%6d:", number);
	printf("%d", number%10);
	if (number<COUNT)
		return number+rec(++number);
	else
		return 0;
}
