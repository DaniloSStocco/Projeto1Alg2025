#ifndef PILHA_H
	#define PILHA_H

    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <stdlib.h>
    #include "paciente.h"
    #include "procedimento.h"
    typedef struct pilha_ PILHA;
    #define TAM 100

    PILHA* pilha_criar();
    void pilha_apagar(PILHA **pilha);
    bool pilha_vazia(PILHA* pilha);
    bool pilha_cheia(PILHA *pilha);
    int pilha_tamanho(PILHA* pilha);
    PROCEDIMENTO* pilha_topo(PILHA* pilha);
    bool pilha_empilhar(PILHA* pilha, PROCEDIMENTO *proc);
    PROCEDIMENTO* pilha_desempilhar(PILHA* pilha);
    bool pilha_imprimir(PILHA *pilha);

#endif