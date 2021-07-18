my_ls: main.o
	gcc -o my_ls main.o

main.o: main.c file_functions.c string_functions.c structs_includes.c
	gcc -c main.c

clean:
	rm *.o my_ls