//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		3
// Task:          		4
// Name:          		aufgabe4.c
// Description:   		Reading of a file in a son process and passing
//						data to another son process via a pipe
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

//////////////////////////////////////////////////////////////////////////////
void hex_print(FILE *dz, char *s)
{	int fd[2],status;
	if ( pipe(fd) != 0)
	{	fprintf(stderr, "Error while creating pipe!\n");
		exit(1);
	}

	printf("Hex print of %s\n\n",s);
	
	// create 1st son (reader)
	switch( fork() )
	{	// fork() error
		case -1 :	fprintf(stderr, "fork() failed!\n");
				exit(1);
				
		// 1st son (reader): reads data from pipe and prints it
		case  0:	{	int i=1;
					unsigned char read_char;
	
					close(fd[1]);	// close writer side of pipe
					while (read(fd[0], &read_char, 1) > 0)
					{	printf(" %02x", read_char);
						if (++i > 16)
						{	printf("\n");
							i=1;
						}
					}
					printf("\n");
					close(fd[0]);	// close reader side of pipe
					exit(1);
				}
	}

	close(fd[0]);		// father: close reader side

	// create 2nd son (writer)
	switch ( fork() )
	{	// fork() error
		case -1:	fprintf(stderr, "fork() failed!\n");
				exit(2);

		// 2nd son (writer): reads from file and writes data to pipe
		case 0:		{	unsigned char c;
					int status;

					close(fd[0]); // close reader side of pipe
					// write bytes to pipe
					while ( fread( &c, 1, 1, dz) > 0)
						write(fd[1], &c, 1);
					close(fd[1]); // close writer side of pipe
					exit(2);
				}
	}
	
	close(fd[1]);		// father: close writer side

	wait(&status);		// wait for 1st son
	wait(&status);		// wait for 2nd son
}

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[] )
{
	FILE *dz;
	int    i;

	if (argc < 2)
	{	fprintf(stderr, "Call: aufgabe4 <filename>\n");
		exit(1);
	}
	for (i=1; i<argc; i++)
	{	if ( ( dz=fopen(argv[i],"rb") ) == NULL )
		{	fprintf(stderr, "Can't open file %s!\n", argv[i]);
			exit(1);
		}
		else
		{	hex_print(dz,argv[i]);
			fclose(dz);
		}
	}
}
