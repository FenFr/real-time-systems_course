# Change the path in the varaiable (FILE) below to include the current programm;
# Then type 'make' into the Terminal to build your Programm
FILE    = Uebung-4/03_Aufgabe_2.c


PATH	= My_Functions/

HEADER  = ${PATH}my_functions.h

OBJECTS = ${PATH}make_child.o ${PATH}power_f.o ${PATH}readc.o ${PATH}string_to_int.o


main:				${FILE} ${OBJECTS}
					gcc -o main.o ${FILE} ${OBJECTS}

make_child.o:	 	${HEADER}
power_f.o:			${HEADER}
readc.o:			${HEADER}
string_to_int.o:	${HEADER}

.PHONY: 			clean
 clean:
				   -rm main.o ${OBJECTS}

# Clean folder by typing in make clean