//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Name:          		readc.c
// Description:   		Reads a string with a certain size from the
//                      standart input
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include "my_functions.h"


void readc(char *arr, int size) {
    char c;
    int  i = 0;

    while( ((c = getc(stdin)) != '\n') && (i < size) )
        arr[i++] = c;

    arr[i] = '\0';
}