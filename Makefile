CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS =


all: calc

calc: calc.o mathlib.o operators.o stack.o
	$(CC) calc.o mathlib.o operators.o stack.o -o calc -lm

calc.o: calc.c messages.h mathlib.h operators.h stack.h
	$(CC) $(CFLAGS) -c $<

mathlib.o: mathlib.c mathlib.h 
	$(CC) $(CFLAGS) -c $<

operators.o: operators.c operators.h stack.h messages.h
	$(CC) $(CFLAGS) -c $<

stack.o: stack.c stack.h messages.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf calc *.o
	rm -rf mathlib *.o
	rm -rf operators *.o
	rm -rf stack *.o


format:
	clang-format -i -style=file *.[ch]



.PHONY: all clean format

