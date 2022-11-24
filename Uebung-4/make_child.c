//////////////////////////////////////////////////////////////////////////////
// Course:	  			Real Time Systems
// Lecturer:      		Dr.-Ing. Frank Golatowski
// Exercise instructor: M.Sc. Michael Rethfeldt
// Author:  			Fenya Freitag
// Name:          		make_child.c
// Description:   		Creates a given number of childs and returns them with
//                      with their individual Child ID (c_id) and Process ID 
//                      (p_id)
//
//                      Return Values (c_id):
//                         -1 ... the function failed / error
//                          0 ... ID of parent process
//                        > 0 ... ID of child  process
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "my_functions.h"


PC_ID make_child(int cc) {

    PC_ID temp;
    temp.p_id = 1;

    for(int i = cc; i > 0; i--) {
        switch(temp.p_id = fork()) {
            case -1 :   temp.c_id = -1;
                        return temp;

            case  0 :   temp.c_id =  i;
                        return temp;
        }
    }

    temp.c_id = 0;
    return temp;
}