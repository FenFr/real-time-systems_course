# Real-Time-Systems

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
|   -1   | creation of child process unsuccessful                                  |
|   0    | returned to newly created child process                                 |
|  > 0   | returned to parent / value == process ID of newly created child process |


#### wait ()
- blocks the parent process till one child process exits or a signal is created 

```c
#include <sys/types.h>
pid_t wait( int *stat_lock );
```


#### execl ()
- 

```c
#include <unistd.h>
int execl( const char *path, "ls", const char *arg_1, ..., NULL );
```