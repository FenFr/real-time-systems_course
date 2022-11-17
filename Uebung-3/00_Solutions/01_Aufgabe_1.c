//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		3
// Task:          		1
// Name:          		01_Aufgabe_1.c
// Description:   		Reading of a file in a father process and
//						passing the data to a son process via a pipe
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>


//////////////////////////////////////////////////////////////////////////////
void hex_print(FILE *dz, char *s)
{	int fd[2];

	if ( pipe(fd) != 0) // initialize pipe
	{	fprintf(stderr, "Error while creating pipe!\n");
		exit(1);
	} else {
		printf("Hex print of %s\n\n",s);
		switch( fork() )
		{
		// fork() error
		case -1:{	fprintf(stderr, "fork() failed\n");
					exit(1);
				}
		// Son: Reads data from the pipe and prints it
		case  0:{	int i=1;
					unsigned char read_char;
					
					// close writer side of pipe
					close(fd[1]);
					while (read(fd[0], &read_char, 1) > 0)
					{
						printf(" %02x", read_char);
						if (++i > 16)
						{
							printf("\n");
							i=1;
						}
					}
					printf("\n");
					close(fd[0]);
					exit(0);
				}
		// Father: Reads from file and writes data to pipe
		default:{	unsigned char c;
					int status;

					// close reader side of pipe
					close(fd[0]);
					// read byte-wise and write to pipe
					while ( fread( &c, 1, 1, dz) > 0)
						write(fd[1], &c, 1);

					// close writer side of pipe after complete transmission
					close(fd[1]);
					wait(&status);
				}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[] )
{	FILE *dz;
	int    i;

	if (argc < 2) // catch case of too few arguments
	{	fprintf(stderr, "Call: aufgabe1 <filename>\n");
		exit(1);
	}
	for (i=1; i<argc; i++) // process all input arguments
	{	if ( ( dz=fopen(argv[i],"rb") ) == NULL ) // read binary
		{	fprintf(stderr, "Can't open file %s!\n", argv[i]);
			exit(1);
		}
		else
		{	hex_print(dz,argv[i]); // print hex values to screen
			fclose(dz);
		}
	}
}
