#include "lista.h"
typedef struct no_ NO;
struct no_{
    ITEM *item;
    NO *anterior;
    NO *proximo;
};
typedef 
struct lista_{
    NO *inicio;
    NO *fim;
    int tamanho;
    bool ordenada;
};

LISTA* LISTA_criar(bool ordenada){
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
        lista->ordenada = ordenada;
    }
    
    return(lista);
}   

void LISTA_esvazia (NO *ptr){
if (ptr != NULL){
    if(ptr->proximo != NULL)
        lista_esvazia(ptr->proximo);

        item_apagar(&ptr->item);
        ptr->anterior = NULL;
        free(ptr); 
        ptr = NULL;
    }
}

bool LISTA_apagar(LISTA **ptr){
    if(*ptr == NULL){
        return;
    }
    LISTA_esvazia((*ptr)->inicio);
    free(*ptr);
    *ptr = NULL;
}

bool LISTA_inserir_inicio(LISTA* lista, ITEM* i){
    if((lista != NULL)&&(!LISTA_cheia(lista))){
        NO *pnovo = (NO*) malloc(sizeof(NO));
        pnovo->item = i;
        if(lista->inicio == NULL){
            lista->fim = pnovo;
            pnovo->proximo = NULL;
        }
        else{
            lista->inicio->anterior = pnovo;
            pnovo->proximo = lista->inicio;
        }
        pnovo->anterior = NULL;
        lista->inicio = pnovo;
        lista->tamanho++;
        return(true);
    }
    else{
        return(false);
    }
}

bool LISTA_inserir_fim(LISTA* lista, ITEM* i){
    if((lista!= NULL) && (!LISTA_cheia(lista))){
        NO* pnovo = (NO*) malloc(sizeof(NO));
        pnovo->item = i;
        if(lista->inicio == NULL){
            lista->inicio = pnovo;
            pnovo->anterior = NULL;
        }
        else{
            lista->fim->proximo = pnovo;
            pnovo->anterior = lista->fim;
        }
        pnovo->proximo = NULL;
        lista->fim = pnovo;
        lista->tamanho++;
        return(true);
    }
    else{
        return(false);
    }
}

ITEM* LISTA_remover(LISTA *lista, int chave){
    NO *p = NULL;
    if( (lista != NULL) && !LISTA_vazia(lista)){
        p = lista->inicio;
        while(p != NULL && (item_get_chave(p->item) != chave)){
            p = p->proximo;
        }
        if(p != NULL){
            if(p == lista->inicio)
                lista->inicio = p->proximo;
            else
                p->anterior->proximo = p->proximo;
            
            if(p == lista->fim)
                lista->fim = p->anterior;
            else
                p->proximo->anterior = p->anterior;
            ITEM *it = p->item;
            p->proximo = NULL;
            p->anterior = NULL;
            free(p);
            lista->tamanho--;
            return(it);
        }
    }
    return(NULL);
}