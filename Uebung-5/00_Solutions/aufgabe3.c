//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		5
// Task:          		3
// Name:          		aufgabe3.c
// Description:   		Recursion and stack size limit
// Compiler call:		cc -o aufgabe3 aufgabe3.c -lpthread
//////////////////////////////////////////////////////////////////////////////
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//////////////////////////////////////////////////////////////////////////////
void* 	threadcode(void *ptr);
int 	rec(int number);
#define COUNT	300000

//////////////////////////////////////////////////////////////////////////////
int main(void)
{	int				number;
	size_t			size;
	pthread_attr_t 	attr;
	pthread_t 		thread1;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &size);
	printf("Stack is: %d.\n", (unsigned int)size);
	size=50000000; // 50 MB
	pthread_attr_setstacksize(&attr, size);
	pthread_attr_getstacksize(&attr, &size);
	printf("Stack is: %d.\n", (unsigned int)size);
	pthread_create(&thread1, &attr, threadcode, 0);
	pthread_join(thread1,0);
	return 0;
}
//////////////////////////////////////////////////////////////////////////////
void* threadcode(void *ptr)
{
	printf("\nResult is: %d.\n", rec(0));
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
int rec(int number)
{
	if (!(number%200))
		printf("\n%6d:", number);
	printf("%d", number%10);
	if (number<COUNT)
		return number+rec(++number);
	else
		return 0;
}
