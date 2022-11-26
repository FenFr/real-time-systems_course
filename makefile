# Change the path in the varaiable (FILE) below to include the current programm;
# Then type 'make' into the Terminal to build your Programm
FILE1    = Uebung-4/04_Aufgabe_2_SENDER.c


WEG		= My_Functions

HEADER 	= ${WEG}/my_functions.h

# Add new Functionalities here
OBJECTS = ${WEG}/make_child.o ${WEG}/power_f.o ${WEG}/readc.o ${WEG}/string_to_int.o


main.o:		${FILE1} ${OBJECTS}
			gcc -o main.o ${FILE1} ${OBJECTS}

${OBJECTS}:	${HEADER}

.PHONY: 	clean
 clean:
		   -rm main.o ${OBJECTS}

# Clean folder by typing in 'make clean'