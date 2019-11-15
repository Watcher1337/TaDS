app.exe: main.o alloc.o fill.o prints.o list.o
	gcc -o app.exe main.o alloc.o fill.o prints.o list.o

main.o: main.c definitions.h alloc.h fill.h prints.h
	gcc -std=c99 -c main.c

alloc.o: alloc.c alloc.h definitions.h
	gcc -std=c99 -c alloc.c

fill.o: fill.h fill.c definitions.h 
	gcc -std=c99 -c fill.c

prints.o: prints.c prints.h definitions.h
	gcc -std=c99 -c prints.c

list.o: list.h list.c
	gcc -std=c99 -c list.h list.c

clean:
	rm -rf *.o *.exe