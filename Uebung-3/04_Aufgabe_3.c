//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenja Freitag
// Exercise:      		3
// Task:          		3
// Name:          		04_Aufgabe_3.c
// Description:   		Signal handler
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>


void sig_h_f();
void sig_h_c(int);


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    pid_t pid_val;
    int fd[2];
    pipe(fd);

    switch (pid_val = fork()) {
        case -1 :   printf("\nError: could not give birth to child!\n");
                    exit(1);
        
        case  0 :   close(fd[1]);
                    pid_t master_val;
                    read(fd[0], &master_val, sizeof(int));
                    signal(SIGINT, sig_h_c);
                    for(int i = 0; i < 10; i++) {
                        sleep(1);
                        printf("PID = %d\n", master_val);                        
                    }
                    exit(2);
                    break;
        
        default :   close(fd[0]);
                    int status;
                    write(fd[1], &pid_val, sizeof(int));
                    signal(SIGINT, sig_h_f);
                    wait(&status);
                    printf("\nThis is parent again!\nPID = %d\n", pid_val);
                    break;
    }

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////


void sig_h_f() {
    printf("\nCan't stop the parent!\n");
}

void sig_h_c(int reason) {
    printf("\nChild terminated: Reason %d\n", reason);
    exit(1);
}