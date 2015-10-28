CFLAGS= -g -Wall -pedantic

lab4a: lab4a.o 
	gcc $(CFLAGS) -o lab4a lab4a.o

clean: lab4a
	rm -f *.o *.~ lab4a *.gch

lab4a.o:
	gcc $(CFLAGS) -c lab4a.c
