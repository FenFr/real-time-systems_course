//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Co-Author:			Fenya Freitag
// Exercise:      		3
// Task:          		1
// Name:          		02_Aufgabe_1.c
// Description:   		Introduction to pipes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>


void hex_print(FILE *dz, char *s) {
	
	int fd[2];

	if (pipe(fd) != 0) {
		fprintf(stderr, "Error while creating pipe!\n");
		exit(1);
	} 
	
	else {
		printf("Hex print of %s\n\n",s);
		
		switch(fork()) {
		// Error Detection
		case -1:{	fprintf(stderr, "fork() failed\n");
					exit(1);
				}
		
		// Child-Process
		case  0:{	int i=1;
					unsigned char read_char;
	
					close(fd[1]);
					while (read(fd[0], &read_char, 1) > 0) {
						printf(" %02x", read_char);
						if (++i > 16) {
							printf("\n");
							i=1;
						}
					}
					printf("\n");
					close(fd[0]);
					exit(0);
				}

		// Parent-Process
		default:{	unsigned char c;
					int status;

					close(fd[0]);
					while (fread(&c,1,1,dz) > 0)
						write(fd[1], &c, 1);
					close(fd[1]);
					wait(&status);
				}
		}
	}
}


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	
	FILE *dz;
	int    i;

	if (argc < 2) {
		fprintf(stderr, "Call: 02_Aufgabe_1 <filename>\n");
		exit(1);
	}
	for (i = 1; i < argc; i++) {
		if ((dz=fopen(argv[i],"rb")) == NULL ) {
			fprintf(stderr,"Can't open file %s\n", argv[i]);
			exit(1);
		} else {
			hex_print(dz,argv[i]);
			fclose(dz);
		}
	}
}

// MAIN END //////////////////////////////////////////////////////////////////