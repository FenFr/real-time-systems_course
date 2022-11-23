//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:              Fenya Freitag
// Exercise:      		2
// Task:          		n.A.
// Name:          		05_command_line_test.c
// Description:   		Testing and demonstrating argv arguments
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>

#define WERT 10


int main(int argc, char**argv) {

    // Print different stuff from argc and argv
    printf("argc  : %d\n", argc);

    for(int i = 0; i < WERT; i++) {
        printf("argv %d: %s\n",i, argv[i]);
    }

    return 0;
}

/*
Schreibe nach dem Kompilieren hinter z.B. ./a.out noch weitere Zeichen oder Zeichenketten.

Bsp.:   ./a.out text
        damit ist argv[1] == "text"

Bsp.:   ./a.out text uwu
        argv[0] == "./a.out"
        argv[1] == "text"
        argv[2] == "uwu"
        argc    ==  3

argc gibt die Anzahl der in der Kommandozeile eingegeben Zeichenketten an.
*/