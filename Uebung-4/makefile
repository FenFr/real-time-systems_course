exercise = 03_Aufgabe_2.c

objects  = make_child.o power_f.o readc.o string_to_int.o


main:				${exercise} ${objects}
					gcc -o main.o ${exercise} ${objects}


make_child.o:		my_functions.h

power_f.o:			my_functions.h

readc.o:			my_functions.h

string_to_int.o:	my_functions.h


.PHONY: 			clean
 clean:
	rm ${objects}

# Clean folder by typing in make clean