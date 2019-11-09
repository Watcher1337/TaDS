app.exe: main.o func_list.o func_arr.o
	gcc -o app.exe main.o func_list.o func_arr.o

main.o: main.c func.h func_arr.h
	gcc -std=c99 -c main.c

func_list.o: func_list.c func.h
	gcc -std=c99 -c func_list.c

func_arr.o: func_arr.h func_arr.c
	gcc -std=c99 -c func_arr.c

test.exe: test.o func.o
	gcc -o test.exe test.o func.o

test.o: test.c func.h
	gcc -std=c99 -Wall -pedantic -Werror -c test.c

clean:
	rm -rf *.o *.exe