CFLAGS= -g -Wall -pedantic

lab4a: lab4a.o graphM.o
	gcc $(CFLAGS) -o lab4a lab4a.o graphM.o

lab4a.o: lab4a.c graphM.h
	gcc $(CFLAGS) -c lab4a.c

graphM.o: graphM.c graphM.h
	gcc $(CFLAGS) -c graphM.c

clean:
	rm -f *.o *.~ lab4a *.gch
