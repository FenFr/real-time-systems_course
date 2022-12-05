//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Exercise:      		5
// Task:          		2
// Name:          		03_Aufgabe_2.c
// Description:   		Creating multiple threads
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <pthread.h>


void routine_1();
void routine_2();


// MAIN //////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    pthread_t threads[2];

    pthread_create(&threads[0], NULL, (void *)routine_1, 0);
    pthread_create(&threads[1], NULL, (void *)routine_2, 0);

    // pthread_join prevents race conditions
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_exit(0);

    return 0;
}

// MAIN END //////////////////////////////////////////////////////////////////


void routine_1() {
    printf("Hello ");
    pthread_exit(0);
}

void routine_2() {
    printf("World\n");
    pthread_exit(0);
}