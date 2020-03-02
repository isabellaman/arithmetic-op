#------------------------------------------------------------------------------
# Makefile for any C program
#------------------------------------------------------------------------------

PROGRAM_NAME = ArithmeticOperations
FLAGS        = -std=c99 -Wall
SOURCE       = $(PROGRAM_NAME).c
OBJECT       = $(PROGRAM_NAME).o
EXEBIN       = $(PROGRAM_NAME)

$(EXEBIN) : $(OBJECT)
	gcc -o $(EXEBIN) $(OBJECT)

$(OBJECT) : $(SOURCE)
	gcc -c $(FLAGS) $(SOURCE)

clean :
	rm $(EXEBIN) $(OBJECT)

memcheck : $(EXEBIN)
	valgrind --leak-check=full $(EXEBIN) in1
