#include "fila.h"
#define TAM_MAX 50

struct fila_{
    ITEM *fila[TAM_MAX];
    int inicio;
    int fim;
    int tamanho;
};

FILA *FILA_criar(void){
    FILA *fila = (FILA*) malloc(sizeof(FILA));
    if(fila != NULL){
        fila->inicio = 0;
        fila->fim = 0;
        fila->tamanho = 0;
    }
    return(fila);
}

bool FILA_cheia(FILA* fila){
    if(fila != NULL){
        return(fila->tamanho == TAM_MAX);
    }
    else{
        return(NULL);
    }
}

bool FILA_vazia(FILA *fila){
    if(fila != NULL){
        return(fila->tamanho == 0);
    }
    else{
        return(NULL);
    }
}

bool FILA_inserir(FILA *fila, ITEM *item){
    if(fila != NULL ){
        if(!FILA_cheia(fila)){
            fila->fila[fila->fim] = item;
            fila->fim = (fila->fim+1)%TAM_MAX;
            fila->tamanho++;

            return(true); 
        }
        //printf("\nFalha na operacao: Fila cheia!");
    }
    else{
        //printf("\nFila não existe!")
        return(NULL);
    }
}

ITEM *FILA_remover(FILA *fila){
    if(fila != NULL){
        if(!FILA_vazia(fila)){
            ITEM *p = fila->fila[fila->inicio];
            fila->fila[fila->inicio] = NULL;
            fila->inicio = (fila->inicio+1)%TAM_MAX;
            fila->tamanho--;
            return(p);
        }
        else{
            //printf("\nFalha na operacao: Fila vazia");
            return(NULL);
        }
    }
    else{
        //printf("\nFila não existe");
        return(NULL);
    }
}

int FILA_tamanho(FILA *fila){
    if(fila != NULL){
        return(fila->tamanho);
    }
    else{
        //printf("\nFila não existe");
        return(NULL);
    }
}

void FILA_imprimir(FILA *fila){
    
}