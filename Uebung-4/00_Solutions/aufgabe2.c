//////////////////////////////////////////////////////////////////////////////
// Course:	  		Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: 	M.Sc. Michael Rethfeldt
// Exercise:      		4
// Task:          		2
// Name:          		aufgabe2.c
// Description:   		Exchange of data between processes using a message queue
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

//#define PERMISSIONS		0666
#define PERMISSIONS		S_IRUSR | S_IWUSR
#define MESSAGE_STRING		"Hello, this is the %2dth son. PID: 0x%x"
#define MESSAGE_SIZE		50
#define DEFAULT_PROCESSCOUNT	20

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
{	key_t	key;
	pid_t	son_pid;
	int 	i, maxprocesses, msqid, retvalue;

	// determine process number
	maxprocesses=DEFAULT_PROCESSCOUNT;
	if ( argc>1 )
	{	if ( sscanf(argv[1], "%d", &i) && i>0 )
			maxprocesses=i;
		else
			printerrorexit("Error getting correct number of processes!", i);
	}
	printf("Number of processes is: %d\n", maxprocesses);

	// determine key of message queue
	key=ftok( argv[0], 2 );
	if ( key==-1 )
		printerrorexit("Error obtaining key_t!", errno);
	printf("Key is: 0x%x\n", key);

	// create and open a system wide IPC-Channel
	if ((msqid = msgget(key, PERMISSIONS | IPC_CREAT)) < 0)
		printerrorexit("Can't create messagequeue!", errno);

	printf("msqid = 0x%x\n", msqid);

	// fork processes
	for ( i=0; i<maxprocesses; i++)
	{	son_pid=fork();
		if (son_pid == -1)			// Error ?
			printerrorexit("Error during fork()!", errno);
		if (!son_pid)				// Is this the son ?
		{
			msgbuf	sendmessage;
			printf("Son 0x%x is starting now!\n", getpid());
			sendmessage.mtype=1;
			snprintf(sendmessage.mtext, MESSAGE_SIZE, MESSAGE_STRING, i, getpid());
			retvalue=msgsnd(msqid, &sendmessage, MESSAGE_SIZE, 0);
			if ( retvalue==-1 )
				printerrorexit("Error sending message!", errno);
			printf("Son 0x%x is exiting now!\n", getpid());
			return 0;
		}
	}

	// the father
	{	msgbuf	receivemessage;
		char	buffer[MESSAGE_SIZE+1];
		int		status;
		printf("The father goes on!\n");

		for (i=0; i<maxprocesses; i++)
		{	// truncate messages automatically !
			retvalue=msgrcv(msqid, &receivemessage, MESSAGE_SIZE, 0, MSG_NOERROR);
			if ( retvalue==-1 )
				printerrorexit("Error receiving message! Error: %d.\n", errno);
			buffer[MESSAGE_SIZE]='\0';
			strncpy(buffer, receivemessage.mtext, MESSAGE_SIZE);
			printf("Message \"%s\" received.\n", buffer);
			son_pid=wait(&status);
			if ( son_pid==-1 )
				fprintf(stderr, "Error waiting child process %d. Errno: %d=%s.\n",
						i, errno, strerror(errno));
			else
				printf("The %2dth son exited with return code: %x | %x\n",
						i, (status>>8) & 0xff, status & 0xff);
		}
	}

	// remove message queue
	retvalue=msgctl(msqid, IPC_RMID, 0);
	if ( retvalue )
		printerrorexit("Error removing message queue!", errno);

	return 0;
}
