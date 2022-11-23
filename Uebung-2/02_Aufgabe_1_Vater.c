//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Co-Author:			Fenya Freitag
// Exercise:      		2
// Task:          		1
// Name:          		02_Aufgabe_1_Vater.c
// Description:   		Father process executes an external son process
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
	
	int status;
	pid_t fork_pid;

	if ( (fork_pid = fork() ) == 0 ) {
		execl("./son", "son", NULL);
		printf("execl() failed!\n");
		exit(3);
	}

	else if (fork_pid == -1) {
		printf("fork() failed!\n");
		exit(2);
	}

	wait(&status); // wait for termination of son

	printf("wait status: 0x%x | 0x%x | 0x%x |\n", status, (status>>8) & 0xff, status & 0xff);

	return 0;
}
