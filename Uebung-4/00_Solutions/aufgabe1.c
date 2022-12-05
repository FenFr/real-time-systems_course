//////////////////////////////////////////////////////////////////////////////
// Course:	  		Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor:		M.Sc. Michael Rethfeldt
// Exercise:      		4
// Task:          		1
// Name:          		aufgabe1.c
// Description:   		Exchange of data using a message queue
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

//#define PERMISSIONS	0666
#define PERMISSIONS	S_IRUSR | S_IWUSR
#define MESSAGE_STRING	"Hello world!"
#define MESSAGE_SIZE	50

//////////////////////////////////////////////////////////////////////////////
typedef struct
{	long	mtype;
	char	mtext[MESSAGE_SIZE];
} msgbuf;

//////////////////////////////////////////////////////////////////////////////
void printerrorexit(char *str, int errornumber)
{	fprintf(stderr, "%s %d=%s\n", str, errornumber, strerror(errornumber));
	exit(errno);
}

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{	int 	msqid, retvalue, status;
	msgbuf	sendmessage, receivemessage;
	char	buffer[MESSAGE_SIZE+1];
	key_t	key;

	// determine key of message queue
	key=ftok( argv[0], 1 );
	if ( key==-1 )
		printerrorexit("Error obtaining key_t!", errno);
	printf("Key is: 0x%x\n", key);

	// create and open a system wide IPC-Channel
	if ((msqid = msgget(key, PERMISSIONS | IPC_CREAT)) < 0)
		printerrorexit("Can't create messagequeue!", errno);
	printf("msqid = 0x%x\n", msqid);

	// transmit message
	sendmessage.mtype=1;
	strncpy(sendmessage.mtext, MESSAGE_STRING, MESSAGE_SIZE);
	retvalue=msgsnd(msqid, &sendmessage, MESSAGE_SIZE, 0);
	if ( retvalue==-1 )
		printerrorexit("Error sending message!", errno);

	// receive message (truncate messages automatically)
	retvalue=msgrcv(msqid, &receivemessage, MESSAGE_SIZE, 0, MSG_NOERROR);
	if ( retvalue==-1 )
		printerrorexit("Error receiving message! Error: %d.\n", errno);
	strncpy(buffer, receivemessage.mtext, MESSAGE_SIZE);
	buffer[MESSAGE_SIZE]='\0';
	printf("Message \"%s\" received.\n", buffer);

	// remove message queue
	retvalue=msgctl(msqid, IPC_RMID, 0);
	if ( retvalue )
		printerrorexit("Error removing message queue!", errno);

	return 0;
}
