#include "pilha.h"
#include "procedimento.h"
    typedef struct no NO;

struct no {
    PROCEDIMENTO *historico;
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

void pilha_apagar(PILHA **pilha) {
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

PROCEDIMENTO* pilha_topo(PILHA* pilha) {
    if ((pilha != NULL) && (!pilha_vazia(pilha)) ){
        return (pilha->topo->historico);
    }
    return (NULL);
}

bool pilha_empilhar(PILHA* pilha, PROCEDIMENTO* proc) {
    if (!pilha_cheia(pilha)) {
        //printf("\npilha empilhar");
        NO* pnovo = (NO *) malloc(sizeof (NO));
        if (pnovo != NULL) {
            pnovo->historico = proc;
            pnovo->anterior = pilha->topo;
            pilha->topo = pnovo;
            pilha->tamanho++;
            //printf("\nFoi empilhado o procedimento %s", proc_get_conteudo(proc));
            return (true);
        }
    }
    return (false);
}

PROCEDIMENTO* pilha_desempilhar(PILHA* pilha) {
    if ((pilha != NULL) && (!pilha_vazia(pilha)) ){
        NO* pno = pilha->topo;
        PROCEDIMENTO* proc = pilha->topo->historico;
        pilha->topo = pilha->topo->anterior;
        pno->anterior=NULL; free(pno); pno=NULL;
        pilha->tamanho--;
        return (proc);
    }
    return (NULL);
}

bool pilha_imprimir(PILHA *pilha){
    //printf("\nCheguei no pilha imprimir");
    if(pilha != NULL && !pilha_vazia(pilha)){
        NO *pno = pilha->topo;
        printf("\n---------PROCEDIMENTOS-----------");
        while(pno != NULL){
            imprimirproc(pno->historico);
            pno = pno->anterior;
        }
        printf("\n---------------------------------");
        return true;
    }
    else{
        printf("\nPilha vazia ou inexistente");
        return false;
    }
}