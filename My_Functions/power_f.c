//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Name:          		power_f.c
// Description:   		Returns the power = base^{exponent}
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include "my_functions.h"


int power_f(int base, int exponent) {
    
    int power = 1;

    for(exponent; 0 < exponent; exponent--)
        power *= base;

    for(exponent; 0 > exponent; exponent++)
        power /= base;
    
    return power;
}