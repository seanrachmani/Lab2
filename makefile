#link
myshell : LineParser.o myshell.o
	gcc -m32 -g -Wall -o myshell LineParser.o myshell.o

#compile 
myshell.o : myshell.c
	gcc -m32 -g -Wall -c -o myshell.o myshell.c

LineParser.o : LineParser.c
	gcc -m32 -g -Wall -c -o LineParser.o LineParser.c	

#clean
clean :
	rm -f *.o myshell