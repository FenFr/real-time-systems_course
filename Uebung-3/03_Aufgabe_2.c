//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenja Freitag
// Exercise:      		3
// Task:          		2
// Name:          		03_Aufgabe_3.c
// Description:   		A example for using the signal() function
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>


void a_function();


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv){

    signal(SIGINT, a_function);

    printf("\nPress Ctrl + C to exit this programm\n");

    while(1){};

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////


void a_function() {
    printf("\nThis is printed, because signal() pointed to this function.\n");
    exit(1);
}