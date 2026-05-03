#link
all : myshell Printers looper

myshell : LineParser.o myshell.o
	gcc -m32 -g -Wall -o myshell LineParser.o myshell.o

Printers : Printers.o
	gcc -m32 -g -Wall -o Printers Printers.o

looper : looper.o
	gcc -m32 -g -Wall -o looper looper.o

#compile 
myshell.o : myshell.c
	gcc -m32 -g -Wall -c -o myshell.o myshell.c

LineParser.o : LineParser.c
	gcc -m32 -g -Wall -c -o LineParser.o LineParser.c	

Printers.o : Printers.c
	gcc -m32 -g -Wall -c -o Printers.o Printers.c

looper.o : looper.c
	gcc -m32 -g -Wall -c -o looper.o looper.c
#clean
clean :
	rm -f *.o myshell Printers looper