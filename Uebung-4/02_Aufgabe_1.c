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


struct msgbuf {
    long mtype;
    char mtext[100];
} s_message, r_message;


void my_read(char *arr, int size) {
    char c;
    int  i = 0;

    while( ((c = getc(stdin)) != '\n') && (i < size) )
        arr[i++] = c;

    arr[i] = '\0';
}


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    // Sending Part
    
    key_t key = ftok("02_Aufgabe_1.c", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    s_message.mtype = 1;
    
    printf("Write Message: ");
    my_read(s_message.mtext, sizeof(s_message.mtext));

    if( (msgsnd(msgid,  &s_message, sizeof(s_message), 0)) == -1 ) {
        printf("Error: Could not send message\n\n");
        exit(1);
    }


    // Recieving Part

    r_message.mtype = 1;

    if( (msgrcv(msgid, &r_message, sizeof(r_message), r_message.mtype, 0)) == -1 ) {
        printf("Error: Could not recieve message\n\n");
        exit(1);
    }

    printf("\nRecieved Message: %s\n\n", r_message.mtext);

    if( (msgctl(msgid, IPC_RMID, NULL)) == -1 ) {
        printf("Error: Fatal\n\n");
        exit(1);        
    }


    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////