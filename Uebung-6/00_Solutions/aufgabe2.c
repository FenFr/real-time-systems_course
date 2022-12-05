//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		6
// Task:          		2
// Name:          		aufgabe2.c
// Description:   		Data exchange with usage of condition variables
// Compiler call:		cc -o aufgabe2 aufgabe2.c -lpthread
//////////////////////////////////////////////////////////////////////////////
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

//////////////////////////////////////////////////////////////////////////////
void* reader_function(void *);
void writer_function(void);

//////////////////////////////////////////////////////////////////////////////
int 				buffer;
int 				buffer_has_item = 0;
pthread_mutex_t 	mutex;
pthread_cond_t		cond_buffer_full;
pthread_cond_t		cond_buffer_empty;

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	pthread_mutexattr_t	mutex_attr;
	pthread_attr_t		attr;
	pthread_t 			reader;

	if ( pthread_mutexattr_init(&mutex_attr) == 0 )
	{	if ( pthread_mutex_init(&mutex, &mutex_attr) == 0 )
		{	if ( pthread_attr_init(&attr) == 0)
			{	pthread_cond_init(&cond_buffer_full, NULL);
				pthread_cond_init(&cond_buffer_empty, NULL);
				if ( pthread_create( &reader, &attr, reader_function, 0 ) == 0 )
				{	writer_function();
					pthread_join(reader,0);
				}
				pthread_cond_destroy(&cond_buffer_full);
				pthread_cond_destroy(&cond_buffer_empty);
			}
			pthread_mutex_destroy( &mutex);
		}
	}
	printf("Main thread finished!\n");
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
void writer_function(void)
{
	int a='a';
	while( a <= 'q' )						// Abort when buffer content > 'q'
	{
		pthread_mutex_lock (&mutex);
		while ( buffer_has_item == 1) {		// wait until buffer is empty
			printf("writer loop\n");
			pthread_cond_wait (&cond_buffer_empty, &mutex);
		}
		buffer=a++;
		buffer_has_item = 1;
		printf("Writer: buffer filled with '%c'.\n",buffer);
		pthread_cond_signal( &cond_buffer_full );
		pthread_mutex_unlock( &mutex );
	}
}

//////////////////////////////////////////////////////////////////////////////
void* reader_function(void *ptr)
{
	int	a=0;
	while( a < 'q' )						// Abort when buffer content == 'q'
	{
		pthread_mutex_lock (&mutex);
		while( buffer_has_item != 1) {		// wait until buffer is full
			printf("reader loop\n");
			pthread_cond_wait (&cond_buffer_full, &mutex);
		}
		a=buffer;
		buffer_has_item = 0;
		printf("Reader: buffer read with '%c'.\n",a);
		pthread_cond_signal( &cond_buffer_empty );
		pthread_mutex_unlock (&mutex);
	}
	printf("Reader thread finished\n");
	return 0;
}
