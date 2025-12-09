#ifndef IO_H
	#define IO_H
    #define TAM 100
	#include "paciente.h"
    #include "avl.h"
    #include "heap.h"
    #include <stdbool.h>

    bool SAVE(AVL *lista, HEAP *fila); // Salva os itens da lista e da fila em arquivos
    bool LOAD(AVL **lista, HEAP **fila); // Carrega os itens dos arquivos na lista e na fila
	  
#endif
