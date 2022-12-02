<div align = "center">
  <h1> Real-Time-Systems </h1>
  <h3> This is my Repository for the Real-Time-Systems course at my University. </h3>
  
  &nbsp;
  
  ![Repository Size][rep-size-img] &nbsp; ![Code Size][code-size-img] &nbsp; ![Code File Size][code-file-img] &nbsp; ![Lines of Code][code-lines-img]

</div>


<!-- Link anchors -->

[code-size-img]:    https://img.shields.io/github/languages/code-size/FenFr/cpp_and_gui_course?label=Code%20Size&style=flat-square
[code-file-img]:    https://img.shields.io/github/directory-file-count/fenfr/cpp_and_gui_course?label=Files&style=flat-square
[code-lines-img]:   https://img.shields.io/tokei/lines/github/fenfr/cpp_and_gui_course?label=Lines%20of%20Code&style=flat-square
[rep-size-img]:     https://img.shields.io/github/repo-size/FenFr/cpp_and_gui_course?label=Repo%20Size&style=flat-square




- [Real-Time-Systems](#real-time-systems)
  - [Commands](#commands)
      - [fork ()](#fork-)
      - [wait ()](#wait-)
      - [pipe ()](#pipe-)
      - [signal ()](#signal-)
      - [execl ()](#execl-)
  - [File In-/Output](#file-in-output)
      - [create ()](#create-)
      - [open ()](#open-)
      - [close ()](#close-)
      - [read ()](#read-)
      - [write ()](#write-)
  - [Message Queue](#message-queue)
      - [msgget ()](#msgget-)
      - [msgsnd ()](#msgsnd-)
      - [msgrcv ()](#msgrcv-)
      - [msgctl ()](#msgctl-)

## Commands

#### fork ()
- creates new process - the child process
- child process starts right after the fork() function was called
- a child process can call another chid processf
- when multiple child processes are called it is uncertain which one will be executed first

```c
#include <unistd.h>
#include <sys/types.h>
pid_t fork( void );
```

| Return | Description                                                             |
| :----: | :---------------------------------------------------------------------- |
|   -1   | Error                                                                   |
|   0    | returned to newly created child process                                 |
|  > 0   | returned to parent / value == process ID of newly created child process |

**Coding examples:**
```c
pid_t pid = fork();

if( pid == -1 ) {
    printf("Error!");   
    exit(1);
}
else if( pid == 0 ) {
    // instructions for child-process
}
else {
    // instructions for parent-process
}
```

```c
switch ( fork() ) {
    case -1 :   printf("Error!");
                exit(1);
              
    case  0 :   // instructions for child-process
                break;
    default :   // instructions for parent-process
                break;
}
```

**Get the current Process ID**
- `getpid()` to get the current Process ID
- `getppid()` to get the parents Process ID
```c
int getpid ( void );
int getppid( void );
```

#### wait ()
- blocks the parent process till one child process exits or a signal is created 
- usually called after `fork()`

```c
#include <sys/wait.h>
pid_t wait( int *stat_lock );
```


#### pipe ()
- connects two processes
- standart output of one process becomes standart input of other process
- one way communication

```c
#include <sys/types.h>
int pipe( int fds[2] );
```

| Return | Description |
| :----: | :---------- |
|   -1   | Error       |
|   0    | Succsess    |

| Parameter | Description                         |
| :-------: | :---------------------------------- |
|   fd[0]   | file descriptor for the 'read end'  |
|   fd[1]   | file descriptor for the 'write end' |


#### signal ()
```c
#include <signal.h>
void *signal( int sig, void (*func)(int) )(int)
```
- `sig` is the signal number to which a handling function is set

|    sig    | Macro & Signal                                                                                                                                                                |
| :-------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `SIGABRT` | (Signal Abort) Abnormal termination, such as is initiated by the function                                                                                                     |
| `SIGFPE`  | (Signal Floating-Point Exception) Erroneous arithmetic operation, such as zero divide or an peration resulting in overflow (not necessarily with a floating-point operation). |
| `SIGILL`  | (Signal Illegal Instruction) Invalid function image, such as an illegal instruction. This is generally due to a corruption in the code or to an attempt to execute data.      |
| `SIGINT`  | (Signal Interrupt) Interactive attention signal. Generally generated by the application user.                                                                                 |
| `SIGSEGV` | (Signal Segmentation Violation) Invalid access to storage − When a program tries to read or write outside the memory it is allocated for it.                                  |
| `SIGTERM` | (Signal Terminate) Termination request sent to program.                                                                                                                       |

- `*func` is a pointer to a function (either defiend by programmer or predefined)

|   func    | Function & Description                                                                     |
| :-------: | :----------------------------------------------------------------------------------------- |
| `SIG_DFL` | Default handling − The signal is handled by the default action for that particular signal. |
| `SIG_IGN` | Ignore Signal − The signal is ignored.                                                     |

|  Return   | Description                          |
| :-------: | :----------------------------------- |
| `SIG_ERR` | Error                                |
|    > 0    | previous value of the signal handler |


#### execl ()
```c
#include <unistd.h>
int execl( const char *path, "ls", const char *arg_1, ..., NULL );
```



## File In-/Output
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int create( char *filename, mode_t mode )
int open  ( const char* path, int flags [ int mode ] ); 
int close ( int fd );
size_t read ( int fd, void* buf, size_t buf_size );
size_t write( int fd, void* buf, size_t buf_size );
```

#### create ()
- create new and empty file
```c
int create( char *filename, mode_t mode )
```
- `filename` : name of the file which you want to create
- `mode` : indicates permissions of new file

| Return | Description          |
| :----: | :------------------- |
|   -1   | Error                |
|  >= 0  | Used File Descriptor |

#### open ()
- opens file for reading, writing or both
```c
int open( const char* path, int flags [ int mode ] ); 
```
- `path` : path to file which you want to use

|   Flags    | Description                           |
| :--------: | :------------------------------------ |
| `O_RDONLY` | read only                             |
| `O_WRONLY` | write only                            |
|  `O_RDWR`  | read and write                        |
| `O_CREAT`  | create file if it doesn’t exist       |
|  `O_EXCL`  | prevent creation if it already exists |

| Return | Description          |
| :----: | :------------------- |
|   -1   | Error                |
|  >= 0  | Used File Descriptor |

#### close ()
- close the file which the file descriptor (`fd`) points to
```c
int close( int fd );
```
| Return | Description |
| :----: | :---------- |
|   -1   | Error       |
|   0    | Succsess    |


#### read ()
```c
size_t read( int fd, void* buf, size_t buf_size );
```
- `fd` : file descriptor
- `buf` : buffer to read data from
- `buf_size` : length of buffer

| Return | Description              |
| :----: | :----------------------- |
|   -1   | Error / Signal Interrupt |
|   0    | EOF                      |
|  > 0   | Number of Bytes Read     |


#### write ()
```c
size_t write( int fd, void* buf, size_t buf_size );
```
- `fd` : file descriptor
- `buf` : buffer to write data to
- `buf_size` : length of buffer

| Return | Description              |
| :----: | :----------------------- |
|   -1   | Error / Signal Interrupt |
|   0    | EOF                      |
|  > 0   | Number of Bytes Read     |


## Message Queue
```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget( key_t key, int msgflg )
int msgsnd( int msgid, const void *msgp, size_t msgsz, int msgflg )
int msgrcv( int msgid, const void *msgp, size_t msgsz, long msgtype, int msgflg )
int msgctl( int msgid, int cmd, struct msqid_ds *buf )
```

#### msgget ()
- creates or allocates a System V message queue

```c
int msgget( key_t key, int msgflg )
```
- `key` : recognizes the message queue / can be an arbitrary value or derivated from `ftok()`
- `msgflg` : specifies required message queue flag/s

| Return | Description              |
| :----: | :----------------------- |
|   -1   | Error                    |
|  >= 0  | Message Queue Identifier |

| Flag  | Description |
| :---: | :---------- |

**ftock ()**
```c
key_t ftok(const char *pathname, int proj_id);
```
- `*pathname` : refers to an existing, accessible file
- `proj_id` : least significant 8 Bit

#### msgsnd ()
- sends/appends a message into the message queue

```c
int msgsnd( int msgid, const void *msgp, size_t msgsz, int msgflg )
```
- `msgid` : message queue identifier (return value of `msgget()`)
- `*msgp` : pointer to the message sent to the caller
- `msgsz` : size of the message send
- `msgflg` : indicates cetain flags

| Return | Description |
| :----: | :---------- |
|   -1   | Error       |
|   0    | Succsess    |


#### msgrcv ()
- retrieves message from the message queue

```c
int msgrcv( int msgid, const void *msgp, size_t msgsz, long msgtype, int msgflg )
```
- `msgid` : message queue identifier (return value of `msgget()`)
- `*msgp` : pointer to the message recieved from the caller
- `msgsz` : size of the message received
- `msgtype` : indicates the type of message
- `msgflg` : indicates certain flags

| Return | Description                         |
| :----: | :---------------------------------- |
|   -1   | Error                               |
|  >= 0  | Number of Bytes received in `mtext` |

| `msgtype` | Description                                                                                     |
| :-------: | :---------------------------------------------------------------------------------------------- |
|     0     | Reads the first received message in the queue                                                   |
|   `+ve`   | Reads the first message in the queue of type msgtype                                            |
|   `-ve`   | Reads the first message of lowest type less than or equal to the absolute value of message type |


#### msgctl ()
- performs control operations of the message queue

```c
int msgctl( int msgid, int cmd, struct msqid_ds *buf )
```
- `msgid` : message queue identifier (return value of `msgget()`)
- `cmd` : command to perform the required control operation on the message queue
- `*buf` : pointer to the message queue structure named struct msqid_ds

| Return | Description                              |
| :----: | :--------------------------------------- |
|   -1   | Error                                    |
|   0    | Nother Operations                        |
|  > 0   | index or identifier of the message queue |

|   `cmd`    | Description                                                                                                                                                                    |
| :--------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `IPC_STAT` | Copies information of the current values of each member of struct msqid_ds to the passed structure pointed by buf. This command requires read permission on the message queue. |
| `IPC_SET`  | Sets the user ID, group ID of the owner, permissions etc pointed to by structure buf.                                                                                          |
| `IPC_RMID` | Removes the message queue immediately.                                                                                                                                         |
| `IPC_INFO` | Returns information about the message queue limits and parameters in the structure pointed by buf, which is of type struct msginfo                                             |
| `MSG_INFO` | Returns an msginfo structure containing information about the consumed system resources by the message queue.                                                                  |
