//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Exercise:      		1
// Task:          		zusatz2
// Name:          		zusatz2.c
// Description:   		?
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	switch ( fork() ) {
	case 0:		printf("Son created\n");
			break;
	default:	switch ( fork() ) {
			case 0: 	printf("Son created\n");
			break;
			default:	printf("Father\n");
					break;
			}
			break;
	}
}

