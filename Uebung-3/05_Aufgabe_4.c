//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:				Fenja Freitag
// Exercise:      		3
// Task:          		4
// Name:          		05_Aufgabe_4.c
// Description:   		Reader and Writer
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>


int birth_child();


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {
	
	int fd[2];
	if( pipe(fd) == -1) {
		printf("\nError: Pipe busted!\n");
		exit(1);
	}

	switch( birth_child(2) ) {
		case -1 :	printf("\nError: Could not birth child!\n");
					exit(1);

		// Parent
		case  0 :	int status_1, status_2;			
					close( fd[1] );
					close( fd[0] );
					wait(&status_1);
					wait(&status_2);
					break;
		
		// Writer Child
		case  1 :	int number_1 = 42069;
					close( fd[0] );
					write( fd[1], &number_1, sizeof(number_1));
					exit(0);

		// Reader Child
		default :	int number_2;
					close( fd[1] );
					read ( fd[0], &number_2, sizeof(number_2));
					printf("Data = %d\n", number_2);
					exit(0);
	}

	return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////


int birth_child(int nbr) {

	pid_t pid_id;

	while( 0 < nbr ) {
		if( (pid_id = fork()) == -1 ) {
			return -1;
		}
		else if( pid_id == 0 )
			return nbr;
		nbr--;
	}

	return 0;
}