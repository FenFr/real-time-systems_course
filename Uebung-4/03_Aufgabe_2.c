//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author   :			Fenya Freitag
// Exercise:      		4
// Task:          		2
// Name:          		03_Aufgabe_1.c
// Description:   		Message queues between multiple processes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../My_Functions/my_functions.h"


struct msgbuf {
    long mtype;
    char mtext[100];
} s_message, r_message;


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    if(!argv[1]) {
        printf("Error: Must give a number behind the function call!\n");
        printf("--> %s NUMBER <--\n\n", argv[0]);
        exit(1);
    }

    // turn argv[1] into a int and spawn that number of childs
    int argv_value  = string_to_int(argv[1]);
    PC_ID pc_id     = make_child(argv_value);

    switch(pc_id.c_id) {
        case -1 :   printf("\nError: Could not make child!\n\n");
                    exit(1);

        // Parent-Process
        case  0 :   printf("I  am  Father  with  P-ID %d\n", pc_id.p_id);
                    break;

        // Child-Processes
        default :   printf("I am Child #%2d with P-ID %d\n", pc_id.c_id, pc_id.p_id);
    }

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////