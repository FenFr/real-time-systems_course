//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Co-Author:			Fenja Freitag
// Exercise:      		2
// Task:          		2
// Name:          		04_Aufgabe_2.c
// Description:   		Demonstrate fork() function call
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
	
	int var;
  
	printf("PID(Father) = %d, var = %d\n", getpid(), var);
  
	if ( fork() == -1 ) {
		fprintf( stderr, "fork() failed!\n" );
	}

	else {
		var++;
		printf("PID = %d, var = %d\n", getpid(), var);

		if ( fork() == -1 ) {
			fprintf( stderr, "Error at 2nd fork()!\n");
		}

		else {
			var++;
			printf("PID = %d, var = %d\n", getpid(), var);
		}
	}

	return 0;
}