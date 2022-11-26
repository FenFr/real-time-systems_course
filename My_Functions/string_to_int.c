//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Name:          		string_to_int.c
// Description:   		Turns a string (only containing of numbers) into
//                      an integer value with the same numbers
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "my_functions.h"


int string_to_int(char *s) {

    int s_size = 0;
    int nbr    = 0;

    // Count the size of the input string and check if it contains any forbiden signs
    for(s_size = 0; s[s_size] != '\0'; s_size++)
        if( (s[s_size] < '0') || (s[s_size] > '9') ) {
            printf("Error: only numbers allowed as input!\n");
            printf("%c is not a valid Input!\n\n", s[s_size]);
            exit(2);
        }

    // Turn every string character into the corresponding int number and add them together
    for(int i = 0; i < s_size; i++) {
        nbr += (int)(s[s_size-i-1] - '0') * power_f(10, i);
    }

    return nbr;
}