//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		2
// Task:          		3
// Name:          		01_Aufgabe_3.c
// Description:   		Creating an arbitrary number of processes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_PROCESSCOUNT 20


//////////////////////////////////////////////////////////////////////////////
void printerrorexit(char *str, int errornumber)
{	fprintf(stderr, "%s %d=%s\n", str, errornumber, strerror(errornumber));
	exit(errno);
}

//////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	int i, maxprocesses, retvalue, sleeptime, createdprocesses=0;
	pid_t son_pid;

	// determine process number
	maxprocesses=DEFAULT_PROCESSCOUNT;
	if ( argc>1 )
	{	if ( sscanf(argv[1], "%d", &i) && i>0 )
			maxprocesses=i;
		else
			printerrorexit("Error getting correct number of processes!", i );
	}
	printf("Number of processes to create: %d\n", maxprocesses);

	// fork processes
	printf("Father pid=%d.\n", getpid() );
	for ( i=0; i<maxprocesses; i++)
	{
		son_pid=fork();
		if ( son_pid == -1 )			// Error ?
			printerrorexit("Error during fork()!", errno );
		if ( ! son_pid )				// Is this the son ?
		{
            srand(time(NULL)*getpid());
			sleeptime=rand()%8;
			printf("Son %d with pid=%d started and is going to sleep now for %d s.\n", i, getpid(), sleeptime);
			sleep( sleeptime );
			printf("Son %d (pid=%d) is exiting now.\n", i, getpid() );
			return i;
		}
		if ( son_pid )
			createdprocesses++;
	}

	// the father
	if ( createdprocesses )
	{
		int	status;
		printf("All processes created. The father goes on!\n");

		for ( i=0; i<createdprocesses; i++)
		{
			son_pid=wait(&status);
			if ( son_pid==-1 )
				fprintf(stderr, "Error waiting child process. Loopcount: %d. Errno: %d=%s.\n",
						i, errno, strerror(errno) );
			else
				printf("Son with pid=%d exited with return code: %d | %d\n",
						son_pid, WEXITSTATUS(status) , status & 0xff);
		}
		printf("All son processes exited!\n");
	}
	return 0;
}
