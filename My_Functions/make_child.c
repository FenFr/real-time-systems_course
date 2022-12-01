//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Name:          		make_child.c
// Description:   		Creates a given number of childs and returns them with
//                      with their individual Child ID (c_id)
//
//                      Return Values for c_id:
//                         -1 ... the function failed / error
//                          0 ... ID of parent process
//                        > 0 ... ID of child  process
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "my_functions.h"


cid_t make_child(int cc) {

    pid_t p_id;

    for(cc; cc > 0; cc--)
        switch(p_id = fork()) {
            case -1 :   return -1;

            case  0 :   return cc;
        }

    return 0;
}