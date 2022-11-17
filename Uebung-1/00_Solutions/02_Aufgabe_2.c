//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		1
// Task:          		2
// Name:          		02_Aufgabe_2.c
// Description:   		Creation of processes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
	int status;
	pid_t fork_pid;
	pid_t my_pid;

	// create the son
	fork_pid=fork();

	// if the fork() call was successful, this is the son
	if (fork_pid == 0)
	{
		sleep(1);
		my_pid = getpid();
		printf("This is the son; PID: %d\n", my_pid);
		exit(3);
	}
	// otherwise, fork() failed
	else if (fork_pid == -1)
	{
		printf("fork() failed !\n");
		exit(2);
	}

	// father process continues here
	printf("This is the father; Son PID: %d\n", fork_pid);

	// the father is in blocked state as long as the son
	// has not terminated. As soon as the son terminates,
	// the father is given its exit code.
	wait(&status);
	printf("wait status: 0x%x | 0x%x | 0x%x |\n", status, (status>>8) & 0xff, status & 0xff);
	return 0;
}
