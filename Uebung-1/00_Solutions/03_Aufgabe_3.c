//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		1
// Task:          		3
// Name:          		03_Aufgabe_3.c
// Description:   		Creation of processes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
	int status,i;
	pid_t pid;

	if ( ( pid=fork() ) == 0 )
	{
		printf("* I am the son. *\n");
		for (i=1; i<=1000000; i++)
		{
			if (i % 100000 == 0)
				printf("Son: | pid: %8d | Loop: %10d |\n", getpid(), i);
		}
		exit(3);
	}
	if ( pid == -1)
	{	printf("fork() failed!\n");
		exit(2);
	}
	for (i=1; i<=1000000; i++)
	{
		if (i % 100000 == 0)
			printf("Father: | pid: %8d | Loop: %10d |\n", getpid(), i);
	}
	wait(&status);		// wait until son ends
	printf("wait status: 0x%x | 0x%x | 0x%x |\n", status, (status>>8) & 0xff, status & 0xff);
	return 0;
}
