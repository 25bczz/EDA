all: prog

prog: main.o menu.o ficheiros.o clientes.o gestores.o meios.o utilidades.o
	gcc -g -o prog main.o menu.o ficheiros.o clientes.o gestores.o meios.o utilidades.o

main.o: main.c menu.h ficheiros.h clientes.h gestores.h meios.h utilidades.h
	gcc -g -o main.o main.c -c

menu.o: menu.c menu.h ficheiros.h clientes.h gestores.h meios.h utilidades.h
	gcc -g -o menu.o menu.c -c

ficheiros.o: ficheiros.c menu.h ficheiros.h clientes.h gestores.h meios.h utilidades.h
	gcc -g -o ficheiros.o ficheiros.c -c

clientes.o: menu.c menu.h ficheiros.h clientes.h gestores.h meios.h utilidades.h
	gcc -g -o clientes.o clientes.c -c

gestores.o: menu.c menu.h ficheiros.h clientes.h gestores.h meios.h utilidades.h
	gcc -g -o gestores.o gestores.c -c

meios.o: menu.c menu.h ficheiros.h clientes.h gestores.h meios.h utilidades.h
	gcc -g -o meios.o meios.c -c

utilidades.o: menu.c menu.h ficheiros.h clientes.h gestores.h meios.h utilidades.h
	gcc -g -o utilidades.o utilidades.c -c

clean:
	del /Q /S *.o *~ math

run:
	MinGW32-make clean
	MinGW32-make all
	./prog