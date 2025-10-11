all: paciente.o lista.o fila.o pilha.o procedimento.o IO.o main.o
	gcc paciente.o lista.o fila.o pilha.o procedimento.o IO.o main.o -o prontosocorro -std=c99 -Wall

paciente.o:
	gcc -c ../paciente.c -I ../ -o paciente.o

lista.o:
	gcc -c lista.c -I ../ -o lista.o

fila.o:
	gcc -c fila.c -I ../ -o fila.o

pilha.o:
	gcc -c pilha.c -I ../ -o pilha.o

procedimento.o:
	gcc -c procedimento.c -I ../ -o procedimento.o

IO.o:
	gcc -c IO.c -I ../ -o IO.o

main.o:
	gcc -c main.c -I ../ -o main.o

clean:
	rm *.o prontosocorro
