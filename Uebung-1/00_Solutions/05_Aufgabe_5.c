//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		1
// Task:          		5
// Name:          		05_Aufgabe_5.c
// Description:   		Execution of external programs
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
	int status;
	pid_t fork_pid;
	pid_t my_pid;

	printf("The father has been created. PID: %d, GID: %d\n", getpid(), getpgid(0));

	// create the son
	fork_pid=fork();

	// if the fork() call was successful, this is the son
	if (fork_pid == 0)
	{
		my_pid = getpid();
		printf("The son has been created\n");
		printf("PID: %d. GID: %d. PID of the father: %d\n", my_pid, getpgid(0), getppid());
		printf("Now exec() is called!\n");
		execl("/bin/bash", "bash", "-c", "ls -lasi ~", (void *)0);
		printf("The program could not be executed!\n" );
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
