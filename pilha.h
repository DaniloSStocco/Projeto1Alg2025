#ifndef PILHA_H
	#define PILHA_H

    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <stdlib.h>
    #include "paciente.h"
    typedef struct pilha_ PILHA;
    #define TAM 100

    PILHA* pilha_criar();
    void pilha_apagar(PILHA **pilha);
    bool pilha_vazia(PILHA* pilha);
    bool pilha_cheia(PILHA *pilha);
    int pilha_tamanho(PILHA* pilha);
    char* pilha_topo(PILHA* pilha);
    bool pilha_empilhar(PILHA* pilha, char hist[]);
    char* pilha_desempilhar(PILHA* pilha);
    bool pilha_imprimir(PILHA *pilha);

#endif