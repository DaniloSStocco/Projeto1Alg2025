all: paciente.o avl.o heap.o IO.o main.o
	gcc paciente.o avl.o heap.o IO.o main.o -o prontosocorro -std=c99 -Wall

paciente.o:
	gcc -c ../paciente.c -I ../ -o paciente.o

avl.o:
	gcc -c avl.c -I ../ -o avl.o

heap.o:
	gcc -c heap.c -I ../ -o heap.o

IO.o:
	gcc -c IO.c -I ../ -o IO.o

main.o:
	gcc -c main.c -I ../ -o main.o

clean:
	rm *.o prontosocorro
