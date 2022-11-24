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


typedef int cid_t;

cid_t make_child(int cc);

int string_to_int(char *s);

int power_f(int base, int exponent);

void readc(char *arr, int size);


#endif