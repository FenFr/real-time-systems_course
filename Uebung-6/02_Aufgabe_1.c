//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Co-Author:			Fenya Freitag
// Exercise:      		6
// Task:          		1
// Name:          		02_Aufgabe_1.c
// Description:   		?
// Compiler call:		cc -o aufgabe1 aufgabe1.c -lpthread
//////////////////////////////////////////////////////////////////////////////


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int		make_new_item(void);
void 	consume_item(char a, int count);
void*	reader_function(void*);
void	writer_function(void);


char 			buffer;
int 			buffer_has_item = 0;
pthread_mutex_t mutex;


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	pthread_mutexattr_t	mutex_attr;
	pthread_attr_t		attr;
	pthread_t 			reader;

	if ( pthread_mutexattr_init(&mutex_attr) == 0 )
	{	if ( pthread_mutex_init(&mutex, &mutex_attr) == 0 )
		{	if ( pthread_attr_init( &attr ) == 0)
			{	if ( pthread_create( &reader,&attr, reader_function,0 ) == 0 )
				{	writer_function();
					pthread_join(reader,0);
				}
			}
			pthread_mutex_destroy( &mutex);
		}
	}
	printf("Main thread finished!\n");
	return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////

void writer_function(void)				// Father
{
	char	a=0;
	int		count=0;

	while( a != 'q' )					// Abort ?
	{	
		pthread_mutex_lock( &mutex );

		if ( buffer_has_item == 0 )
		{
			a = make_new_item();
			buffer=a;
			buffer_has_item = 1;
			printf("Thread 1: buffer: '%c', loop count=%d\n", a, count);
			count=0;
		}
		else
			count++;

		pthread_mutex_unlock( &mutex );
	}
}


void* reader_function(void *ptr)		// Son
{
	char	a=0;
	int		count=0;

	while( a != 'q' )					// Abort ?
	{
		pthread_mutex_lock( &mutex );

		if ( buffer_has_item == 1)
		{	a=buffer;
			if ( a != 'q' )
				consume_item(a,count);
			buffer_has_item = 0;
			count=0;
		}
		else
			count++;

		pthread_mutex_unlock( &mutex );
	}
	printf("Reader thread finished\n");
	return 0;
}


int make_new_item()
{
	static int buffer='a';
	return buffer++;
}


void consume_item(char a, int count)
{
	printf("Thread 2: buffer read with '%c', loop count=%d\n", a, count);
}
