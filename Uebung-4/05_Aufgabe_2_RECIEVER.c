//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:   			Fenya Freitag
// Exercise:      		4
// Task:          		2
// Name:          		04_Aufgabe_2_RECIEVER.c
// Description:   		
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msgbuf {
    long mtype;
    char mtext[50];
} message;


void close_queue(int m_id);


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    message.mtype = 1;

    // Create a message queue
    key_t key = ftok("03_Aufgabe_2_RECIEVER.c", 420);
    int msg_id;
    if( (msg_id = msgget(key, 0666 | IPC_CREAT)) == -1 ) {
        printf("\nError: Can't make Message Queue\n\n");
        exit(1);
    }


    // A signal to close the Message Queue when [Cntr + C] is pressed
    signal(SIGINT, close_queue);


    // Recieve periodic message 
    while(1) {
        msgrcv(msg_id, &message, sizeof(message), 1, 0);
        printf("%s\n", message.mtext);
    }
    


    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////


void close_queue(int m_id) {
    msgctl(m_id, IPC_RMID, NULL);
    printf("\n\nMessage Queue closed, leaving program.\n\n");
    exit(1);
}