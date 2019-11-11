app.exe: main.o func_list.o func_arr.o compare.o
	gcc -o app.exe func_list.o func_arr.o main.o  compare.o

main.o: main.c func_list.h func_arr.h
	gcc -std=c99 -c main.c

func_list.o: func_list.c func_list.h
	gcc -std=c99 -c func_list.c

func_arr.o: func_arr.h func_arr.c
	gcc -std=c99 -c func_arr.c

compare.o: compare.h func_arr.h func_list.h compare.c 
	gcc -std=c99 -c compare.c