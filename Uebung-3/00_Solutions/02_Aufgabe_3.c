//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		3
// Task:          		3
// Name:          		aufgabe3.c
// Description:   		Demonstration of a signal handler.
//						Example for catching SIGINT (Ctrl+C)
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>

void father_signal_handler(int);
void son_signal_handler(int);

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[] )
{	
	pid_t	pid;
	int	status;
	switch ( pid=fork() )
	{
	// Error
	case -1:	printf("Error creating child!\n");
				break;
	// Father:
	default:	signal( SIGINT, father_signal_handler);
				wait(&status);
				printf("Status: %d\n", status>>8);
				break;
	// Son
	case 0:		{	int i;
				pid=getpid();
				signal( SIGINT, son_signal_handler);
				printf("Son started!\n");
				for (i=0; i<10; i++)
				{
					sleep(1);
					//alarm(1);
					//pause();
					printf("%d, Loop %d\n", pid, i);
				}
				exit(0);
				}
				break;
	}
}

//////////////////////////////////////////////////////////////////////////////
void father_signal_handler(int signalnumber)
{
	printf("Father: signal %d caught and ignored!\n", signalnumber);
}

//////////////////////////////////////////////////////////////////////////////
void son_signal_handler(int signalnumber)
{
	printf("Son: signal %d caught and executed!\n", signalnumber);
	exit(2);
}
