//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:   			Fenya Freitag
// Exercise:      		4
// Task:          		2
// Name:          		03_Aufgabe_2.c
// Description:   		Message queues between multiple processes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../My_Functions/my_functions.h"


struct msgbuf {
    long mtype;
    char mtext[100];
} message;


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    if(!argv[1]) {
        printf("Error: Must give a number behind the function call!\n");
        printf("--> %s NUMBER <--\n\n", argv[0]);
        exit(1);
    }

    message.mtype = 1;

    // Create a message queue
    key_t key = ftok("03_Aufgabe_2.c", 99);
    int msg_id;
    if( (msg_id = msgget(key, 0666 | IPC_CREAT)) == -1 ) {
        printf("\nError: Can't make Message Queue\n\n");
        exit(1);
    }

    // Turn argv[1] into a int and spawn that number of childs
    int argv_value = string_to_int(argv[1]);
    cid_t c_id     = make_child(argv_value);

    switch(c_id) {
        case -1 :   printf("\nError: Could not make child!\n\n");
                    exit(1);


        // Parent-Process
        case  0 :   // int status;
                    // wait(&status);
                    for(int i = 0; i < argv_value; i++) {
                        msgrcv(msg_id, &message, sizeof(message), 1, 0);
                        printf("%s\n", message.mtext);
                    }
                    msgctl(msg_id, IPC_RMID, NULL);
                    break;


        // Child-Processes
        default :   sprintf(message.mtext, "This is Child #%2d with P-ID %d", c_id, getpid());
                    if( msgsnd( msg_id, &message, sizeof(message), 0 )) {
                        printf("\nError: Could not send Message\n\n");
                        exit(1);
                    }
    }

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////