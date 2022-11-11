//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		1
// Task:          		2
// Name:          		aufgabe2.c
// Description:   		?
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BIG_N 1000000


int main(void)
{
	int status;
	pid_t fork_pid;

	if ( (fork_pid = fork() ) == 0 ) {	
/*
		for(int i = 0; i < BIG_N; i++) {
			if( (i % 100000) == 0 )
				printf("S: %d\n", i);
		}
*/
		const char *path  = "/usr/bin/ls";
		const char *arg_1 = "-lasi";
		const char *arg_2 = "/home/jf326";

		if (execl(path, "ls", arg_1, arg_2,  NULL) == -1)
			printf("Didn't work\n");

		printf("\n\n* I am the son. *\n");
		exit(3);
	}
/*
	else if (fork_pid > 0) {
		for(int i = 0; i < BIG_N; i++) {
			if( (i % 100000) == 0 )
				printf("F: %d\n", i);
		}
	}
*/
	else if (fork_pid == -1) {
		printf("fork() failed!\n");
		exit(2);
	}

	wait(&status);		                      // wait for termination of son process

	printf("wait status: 0x%x | 0x%x | 0x%x |\n", status, (status>>8) & 0xff, status & 0xff);

	return 0;
}