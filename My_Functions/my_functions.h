//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Name:          		child-spawner
// Description:   		A Header for all my functions
//////////////////////////////////////////////////////////////////////////////


#ifndef my_functions
#define my_functions


typedef int cid_t, pid_t;

typedef struct {
    cid_t c_id;
    pid_t p_id;
} PC_ID;


PC_ID make_child(int cc);

int string_to_int(char *s);

int power_f(int base, int exponent);

void readc(char *arr, int size);


#endif