//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Exercise:      		4
// Task:          		2
// Name:          		04_Aufgabe_2_SENDER.c
// Description:   		
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#include "../My_Functions/my_functions.h"


struct msgbuf {
    long mtype;
    char mtext[50];
} message;


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    switch(argc) {
        case 1  :   printf("Error: Must give a number behind the function call!\n");
                    printf("--> %s time_intervall <--\n\n", argv[0]);
                    exit(1);
                    break;

        default :   break;
    }


    struct timespec clk_time;
    pid_t p_id = getpid();
    message.mtype = 1;


    // Create a message queue
    key_t key = ftok("03_Aufgabe_2_RECIEVER.c", 420);
    int msg_id;
    if( (msg_id = msgget(key, 0666 | IPC_CREAT)) == -1 ) {
        printf("\nError: Can't make Message Queue\n\n");
        exit(1);
    }


    // Turn argv[1] into an int-value
    int argv_value = string_to_int(argv[1]);


    // Send periodic message
    while(1) {

        // Get the clocktime of Linux and write it to the variable clk_time
        if( clock_gettime(CLOCK_MONOTONIC, &clk_time) == -1 ) {
            printf("\nError: Could not get clocktime\n\n");
            exit(1);
        }

        // Send the following message to the Message Queue
        sprintf(message.mtext, "This is P-ID %d with Time %ld.%09ld", p_id, clk_time.tv_sec, clk_time.tv_nsec);
        // printf("Sending Message: %s\n", message.mtext);
        if( msgsnd( msg_id, &message, sizeof(message), 0 )) {
            printf("\nError: Could not send Message\n\n");
            exit(1);
        }

        sleep(argv_value);
    }

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////