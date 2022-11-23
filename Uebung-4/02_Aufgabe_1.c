//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Exercise:      		4
// Task:          		1
// Name:          		02_Aufgabe_1.c
// Description:   		Message queue within a single process
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ipc.h>        // for ftok()


struct msgbuf {
    long mtype;
    char mtext[100];
};


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    key_t key = ftok("02_Aufgabe_1.c", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msgbuf message;
    message.mtype = 1;
    
    printf("Write Message: ");
    gets()

    if( (msgsnd(key,  &message, sizeof(message), 0)) == -1 ) {
        printf("Error: Could not send message");
        exit(1);
    }

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////