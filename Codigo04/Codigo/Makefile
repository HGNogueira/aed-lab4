CFLAGS= -g -Wall -pedantic

lab4a: lab4a.o graphM.o
	gcc $(CFLAGS) -o lab4a lab4a.o graphM.o

lab4a.o: lab4a.c graphM.h
	gcc $(CFLAGS) -c lab4a.c

graphM.o: graphM.c graphM.h
	gcc $(CFLAGS) -c graphM.c

lab4b: lab4b.o graphL.o LinkedList.o
	gcc $(CFLAGS) -o lab4b lab4b.o graphL.o LinkedList.o

lab4b.o:
	gcc $(CFLAGS) -c lab4b.c

graphL.o:
	gcc $(CFLAGS) -c graphL.c

LinkedList.o:
	gcc $(CFLAGS) -c LinkedList.c

clean:
	rm -f *.o *.~ lab4a *.gch
	rm -f *.o *.~ lab4b *.gch
