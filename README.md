# Real-Time-Systems

- [Real-Time-Systems](#real-time-systems)
  - [Commands](#commands)
      - [fork ()](#fork-)
      - [wait ()](#wait-)
      - [pipe ()](#pipe-)
      - [execl ()](#execl-)
  - [Concepts](#concepts)
    - [Signals](#signals)
    - [Message Queues](#message-queues)

## Commands

#### fork ()
- creates new process - the child process
- 

```c
#include <sys/types.h>
pid_t fork( void );
```

| Return | Meaning                                                                 |
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
    case -1 : { printf("Error!");
                exit(1);
              }
    case  0 : // instructions for child-process
              break;
    default : // instructions for parent-process
              break;
}
```


#### wait ()
- blocks the parent process till one child process exits or a signal is created 
- usually called after `fork()`

```c
#include <sys/types.h>
pid_t wait( int *stat_lock );
```


#### pipe ()
-

```c
#include <sys/types.h>
int pipe( int fds[2] );
```

| Return | Meaning  |
| :----: | :------- |
|   -1   | Error    |
|   0    | Succsess |

| Parameter | Meaning                             |
| :-------: | :---------------------------------- |
|   fd[0]   | file descriptor for the 'read end'  |
|   fd[1]   | file descriptor for the 'write end' |


#### execl ()
- 

```c
#include <unistd.h>
int execl( const char *path, "ls", const char *arg_1, ..., NULL );
```


## Concepts


### Signals


### Message Queues
