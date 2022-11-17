//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Co-Author:			Fenja Freitag
// Exercise:      		4
// Task:          		5
// Name:          		04_Aufgabe_5.c
// Description:   		Exchange of data between independent processes using shared memory
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////////////
//#define PERMISSIONS		0666
#define PERMISSIONS		S_IRUSR | S_IWUSR
#define MAXBUFFER  		20000
#define SEMAPHORE_NUMBER	0
#define LOCK_SEMAPHORE(id)	{ if ( semop(id, &(sem_lock[0]), 1 )==-1 )\
									printerrorexit("Error locking semaphore!", errno ); }
#define UNLOCK_SEMAPHORE(id) 	{ if ( semop(id, &(sem_unlock[0]), 1)==-1 )\
									printerrorexit("Error unlocking semaphore!", errno ); }

//////////////////////////////////////////////////////////////////////////////
typedef struct
{		long	exitcount;
		char	buf[MAXBUFFER];
} shared_mem;
union semun					// should be defined in sys/sem.h
{	int val;				// value for SETVAL
	struct semid_ds *buf;			// buffer for IPC_STAT, IPC_SET
	unsigned short *array;			// array for GETALL, SETALL
									// Linux specific part:
	struct seminfo *__buf;			// buffer for IPC_INFO
};

static struct sembuf sem_lock[1]=
{	SEMAPHORE_NUMBER, -1,	0		// semaphore 0, operation decrement by 1, flags=0
};
static struct sembuf sem_unlock[1]=
{	SEMAPHORE_NUMBER, 1,	0		// semaphore 0, operation increment by 1, flags=0
};

//////////////////////////////////////////////////////////////////////////////
void printerrorexit(char *str, int errornumber)
{	fprintf(stderr, "%s %d=%s\n", str, errornumber, strerror(errornumber));
	exit(errno);
}

//////////////////////////////////////////////////////////////////////////////
// argv[1] = name of semaphore/shared memory pair
int main(int argc, char *argv[])
{	key_t		semkey, shmkey;
	int 		i, semid, exitconsumer=0, shmid;
	shared_mem	*shmem;
	union semun	semopts;

	// create semaphore key
	semkey=ftok( argv[1], 1 );
	if ( semkey==-1 )
		printerrorexit("Error obtaining semaphore key_t!", errno);
	printf("SemKey is: 0x%x\n", semkey);

	// create semaphore
	if ((semid = semget(semkey, SEMAPHORE_NUMBER+1, PERMISSIONS | IPC_CREAT)) < 0)
		printerrorexit("Can't create semaphore!", errno);
	semopts.val = 1;
	semctl(semid, SEMAPHORE_NUMBER, SETVAL, semopts);

	// create shared memory key
	shmkey=ftok( argv[1], 2 );
	if ( shmkey==-1 )
		printerrorexit("Error obtaining shared memory key_t!", errno);
	printf("ShmKey is: 0x%x\n", shmkey);

	// create shared memory key
	if ((shmid = shmget(shmkey, sizeof(shared_mem), PERMISSIONS | IPC_CREAT)) < 0)
		printerrorexit("Can't create shared memory segment!", errno);

	// attach shared memory segment to current process
	if (!(shmem = (shared_mem*) shmat(shmid, 0, 0)))
		printerrorexit("Can't attach shared memory segment!", errno);

	shmem->exitcount=0;
	shmem->buf[0]=0;

	// Read data from shared memory
	while(!exitconsumer)
	{	LOCK_SEMAPHORE(semid);
		if ( shmem->buf[0] != 0 )
		{	char *ptr=shmem->buf;
			while(*ptr)
			{	if ( *ptr==EOF )
					exitconsumer=1;
				ptr++;
			}
			printf("%s", shmem->buf);
		}
		shmem->buf[0]=0;
		UNLOCK_SEMAPHORE(semid);
	}

	// Remove shared memory from system
	if ( shmctl(shmid, IPC_RMID, 0) )
		printerrorexit("Error removing shared memory!", errno);

	// Remove semaphore from system
	if ( semctl(semid, IPC_RMID, 0) )
		printerrorexit("Error removing semaphore!", errno);

	return 0;
}
