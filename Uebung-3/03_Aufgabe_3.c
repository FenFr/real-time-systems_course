//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenja Freitag
// Exercise:      		3
// Task:          		3
// Name:          		02_Aufgabe_1.c
// Description:   		Introduction to pipes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    pid_t pid_val;

    // birth child
    if( (pid_val = fork()) == -1 ) {
        printf("Error: can't birth child\n\n");
        exit(1);
    }
    
    // print PID and sleep
    if( pid_val == 0) {
        for( int i = 0; i < 10; i++) {
            printf("PID = %d\n", pid_val);
            sleep(1);
        }
    }

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////*