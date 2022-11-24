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

    for(s_size = 0; s[s_size] != '\0'; s_size++)
        switch (s[s_size]) {
            case '0' :  continue;
            case '1' :  continue;
            case '2' :  continue;
            case '3' :  continue;
            case '4' :  continue;
            case '5' :  continue;
            case '6' :  continue;
            case '7' :  continue;
            case '8' :  continue;
            case '9' :  continue;
            case '\0':  break;
            default  :  printf("Error: only numbers allowed as input!\n");
                        printf("%c is not a valid Input!\n\n", s[s_size]);
                        exit(2);
        }

    for(int i = 0; i < s_size; i++) {                   // '0' == 48 and '9' == 57
        nbr += (s[s_size-i-1] - 48) * power_f(10, i);   // (base 10, exponent i) * (corresponding int value for char)
    }

    return nbr;
}