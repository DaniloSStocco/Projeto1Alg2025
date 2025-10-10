#include "pilha.h"
    typedef struct no NO;

struct no {
    char historico[100];
    NO* anterior;
};

struct pilha_ {
    NO* topo;
    int tamanho;
};

PILHA* pilha_criar() {
    PILHA* pilha = (PILHA *) malloc(sizeof (PILHA));
    if (pilha != NULL) {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }
        return (pilha);
}

void pilha_apagar(PILHA** pilha) {
    NO* paux;
    if ( ((*pilha) != NULL) && (!pilha_vazia(*pilha)) ) {

    while ((*pilha)->topo != NULL) {
    paux = (*pilha)->topo;
    (*pilha)->topo = (*pilha)->topo->anterior;
    paux->anterior = NULL;
    free(paux); paux = NULL;
    }
    }
    free(*pilha);
    *pilha = NULL;
}

bool pilha_vazia(PILHA* pilha) {
    if (pilha != NULL)
        return ((pilha->tamanho == 0) ? true : false);
    return(false);
}

bool pilha_cheia(PILHA *pilha) {
    if (pilha->tamanho >= 10){
        return(true);
    }
    else{
        return(false);
    }
}

int pilha_tamanho(PILHA* pilha) {
    return ((pilha != NULL) ? pilha->tamanho : -1);
}

char* pilha_topo(PILHA* pilha) {
    if ((pilha != NULL) && (!pilha_vazia(pilha)) ){
        return (pilha->topo->historico);
    }
    return (NULL);
}

bool pilha_empilhar(PILHA* pilha, char hist[]) {
    if (!pilha_cheia(pilha)) {
        NO* pnovo = (NO *) malloc(sizeof (NO));
        if (pnovo != NULL) {
            strcopy(pnovo->historico, hist);
            pnovo->anterior = pilha->topo;
            pilha->topo = pnovo;
            pilha->tamanho++;
            return (true);
        }
    }
    return (false);
}

char* pilha_desempilhar(PILHA* pilha) {
    if ((pilha != NULL) && (!pilha_vazia(pilha)) ){
        NO* pno = pilha->topo;
        char hist[] = pilha->topo->historico;
        pilha->topo = pilha->topo->anterior;
        pno->anterior=NULL; free(pno); pno=NULL;
        pilha->tamanho--;
        return (hist);
    }
    return (NULL);
}