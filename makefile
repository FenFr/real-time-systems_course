# Change the path in the varaiable (FILE) below to include the current programm;
# Then type 'make' into the Terminal to build your Programm
FILE    = Uebung-4/03_Aufgabe_2.c


WEG	= My_Functions

HEADER  = ${WEG}/my_functions.h

# Add new Functionalities here
OBJECTS = ${WEG}/make_child.o ${WEG}/power_f.o ${WEG}/readc.o ${WEG}/string_to_int.o


main.o:		${FILE} ${OBJECTS}
			gcc -o main.o ${FILE} ${OBJECTS}

${OBJECTS}:	${HEADER}

.PHONY: 	clean
 clean:
		   -rm main.o ${OBJECTS}

# Clean folder by typing in 'make clean'