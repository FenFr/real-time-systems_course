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

    while(0 < exponent--)
        power *= base;
    
    return power;
}