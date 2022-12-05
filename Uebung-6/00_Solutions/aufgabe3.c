//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		6
// Task:          		3
// Name:          		aufgabe3.c
// Description:   		Synchronization with semaphores
// Compiler call:		cc -o aufgabe3 aufgabe3.c -lpthread
//////////////////////////////////////////////////////////////////////////////
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>

//////////////////////////////////////////////////////////////////////////////
int		make_new_item(void);
void	consume_item(int a);
void*	reader_function(void *);
void*	writer_function(void *);
int		buffer;
sem_t	writers_turn;
sem_t	readers_turn;

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	pthread_attr_t	attr;
	pthread_t 		reader, writer;

	// 0=local process, 0=initial state (read is not allowed)
	if ( sem_init( &readers_turn, 0, 0 ) == 0 )
	{	// 0=local process, 1=initial state (1 write is allowed)
		if ( sem_init( &writers_turn, 0, 1 ) == 0)
		{	if ( pthread_attr_init( &attr ) == 0 )
			{	if ( pthread_create( &reader, &attr, reader_function, NULL) == 0 )
				{	if ( pthread_create( &writer, &attr, writer_function, NULL) == 0)
					{	pthread_join(reader,0);
						pthread_join(writer,0);
					}
					else
					{	pthread_cancel(reader);
						pthread_join(reader,0);
					}
				}
			}
			sem_destroy( &writers_turn);
		}
		sem_destroy( &readers_turn);
	}
	printf("Main thread finished!\n");
}

//////////////////////////////////////////////////////////////////////////////
void* writer_function(void *ptr)
{
	char a=0;
	while(a!='q')
	{
		sem_wait( &writers_turn );
		a = buffer = make_new_item();
		sem_post( &readers_turn );
	}
	printf("Writer thread finished!\n");
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
void* reader_function(void *ptr)
{
	char a=0;
	while(1)
	{
		sem_wait( &readers_turn );
		a=buffer;
		sem_post( &writers_turn );
		if ( a=='q')
			break;
		consume_item( a );
	}
	printf("Reader thread finished!\n");
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
int make_new_item()
{
	static int buffer='a';
	return buffer++;;
}

//////////////////////////////////////////////////////////////////////////////
void consume_item(int a)
{
	if (a>=32)
		printf("ASCII code of '%c': %d\n", a, a);
}
