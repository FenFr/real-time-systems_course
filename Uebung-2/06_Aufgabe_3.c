//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenja Freitag
// Exercise:      		2
// Task:          		3
// Name:          		06_Aufgabe_3.c
// Description:   		Arbitrary number of processes
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int power_f(int base, int exponent);                // returns the power = base^{exponent}

int sti(char *s);                                   // turn a string of numbers into an integer

void pseudo_random(int *arr, int size, int max);    // gives an array of pseudo-random-numbers

int child_spawner(int cc);                          // spawns the given number of childs and returns the number of the child


// MAIN ////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {

    if(!argv[1]) {
        printf("Error: Must give a number behind the function call!\n");
        printf("--> %s NUMBER <--\n\n", argv[0]);
        exit(1);
    }

    int argv_value = sti(argv[1]);

    // create pseudo-random-number-array
    int rng[argv_value];
    pseudo_random(rng, argv_value, 10);

    // spawn the child processes
    int child_number;
    child_number = child_spawner(argv_value);

    // let them sleep for randomm times
    if(child_number > 0) {
        printf("Child %2d is going to sleep for %2d s\n", child_number, rng[child_number-1]);
        sleep(rng[child_number-1]);
        printf("Child %2d wakes up\n", child_number);
    }

    return 0;
}

// MAIN END ////////////////////////////////////////////////////////////////////////////////


int power_f(int base, int exponent) {
    
    int power = 1;

    while(0 < exponent--)
        power *= base;
    
    return power;
}


int sti(char *s) {

    int s_size = 0;
    int nbr    = 0;

    for(s_size = 0; s[s_size] != '\0'; s_size++)
        switch (s[s_size]) {
            case '0' : continue;
            case '1' : continue;
            case '2' : continue;
            case '3' : continue;
            case '4' : continue;
            case '5' : continue;
            case '6' : continue;
            case '7' : continue;
            case '8' : continue;
            case '9' : continue;
            case '\0': break;
            default  :  {   printf("Error: only numbers allowed as input!\n");
                            printf("%c is not a valid Input!\n\n", s[s_size]);
                            exit(3);
                        }
        }

    for(int i = 0; i < s_size; i++) {                   // '0' == 48 and '9' == 57
        nbr += (s[s_size-i-1] - 48) * power_f(10, i);
    }

    return nbr;
}


void pseudo_random(int *arr, int size, int max) {
    
    int c = rand();
    while(c > max)
        c /= 10;
    int m = size + c;
    int a = (m < 2) ? 1 : m/2 + 1;
    
    arr[0] = m - a;

    for(int i = 1; i < size; i++) {
        arr[i] = (a * arr[i-1] + c) % m;
        while(arr[i] > max)
            arr[i] /= 10;
    }
}


int child_spawner(int cc) {

    pid_t fork_pid = 1;
    int child_counter = 0;

    for(int i = cc; i > 0; i--) {
        if(fork_pid > 0) 
            fork_pid = fork();

        else if(fork_pid == -1) {
            printf("Error: Could not give birth to child");
            exit(4);
        }
        if(fork_pid == 0)
            return i;
    }

    return 0;
}