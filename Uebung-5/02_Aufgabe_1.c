//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Exercise:      		5
// Task:          		1
// Name:          		02_Aufgabe_1.c
// Description:   		Thread creation
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// #include "../My_Functions/my_functions.h"


void simple_routine();


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    pthread_t thread;

    if( pthread_create(&thread, NULL, (void *)simple_routine, 0) > 0) {
        perror("Error: Could not create Thread");
        exit(1);
    }
    pthread_exit(0);

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////


void simple_routine() {
    printf("Hello World\n");
    pthread_exit(0);
}