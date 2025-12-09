#ifndef HEAP_H 
    #define HEAP_H

    #include "paciente.h"
    #include <stdbool.h>
    

    typedef struct heap_ HEAP;

    HEAP *heap_criar(void);
    void heap_destruir(HEAP* h);

    bool heap_vazia(HEAP *h);

    bool heap_inserir(HEAP *h, PACIENTE *p);

    PACIENTE* heap_remover(HEAP* h);

    PACIENTE* heap_topo(HEAP* h);

    void heap_imprimir(HEAP* h);

    PACIENTE* heap_buscar(HEAP* h, int id);
#endif
