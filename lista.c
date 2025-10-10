#include "lista.h"
#include "pilha.h"

typedef struct no_ NO;
struct no_{
    PACIENTE *paciente;
    NO *anterior;
    NO *proximo;
};

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

void LISTA_esvazia(NO *ptr){
if (ptr != NULL){
    if(ptr->proximo != NULL){
        LISTA_esvazia(ptr->proximo);
    }
        pac_apagar(&ptr->paciente);
        ptr->anterior = NULL;
        free(ptr); 
        ptr = NULL;
    }
}

bool LISTA_vazia(LISTA* lista){
    if(lista->tamanho == 0){
        return(true);
    }
    else{
        return(false);
    }
}

bool LISTA_apagar(LISTA **ptr){
    if(*ptr == NULL){
        return false;
    }
    LISTA_esvazia((*ptr)->inicio);
    free(*ptr);
    *ptr = NULL;
    return true;
}


bool LISTA_inserir_inicio(LISTA* lista, PACIENTE* pac){
    if((lista != NULL)){
        NO *pnovo = (NO*) malloc(sizeof(NO));
        pnovo->paciente = pac;
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

bool LISTA_inserir_fim(LISTA* lista, PACIENTE* pac){
    if((lista!= NULL)){
        NO* pnovo = (NO*) malloc(sizeof(NO));
        pnovo->paciente = pac;
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

bool LISTA_inserir(LISTA *lista,PACIENTE *pac){
    return LISTA_inserir_fim(lista, pac);
}

PACIENTE* LISTA_buscar(LISTA *lista, int chave){
    NO *p;
    if (lista != NULL){
        p = lista->inicio;
        while (p != NULL) {  
            if (pac_get_id(p->paciente) == chave)
                {return (p->paciente);}
            p = p->proximo;
        }
    }
    return(NULL);
}

PACIENTE* LISTA_remover(LISTA *lista, int chave){
    NO *p = NULL;
    if( (lista != NULL) && !LISTA_vazia(lista)){
        p = lista->inicio;
        while(p->proximo != NULL && (pac_get_id(p->paciente) != chave)){
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
            PACIENTE *pac = p->paciente;
            p->proximo = NULL;
            p->anterior = NULL;
            pilha_apagar(pac_get_refpilha(pac));
            free(p);
            lista->tamanho--;
            return(pac);
        }
    }
    return(NULL);
}

bool adicionar_historico(LISTA* lista, int id, char hist[]){
    printf("Cheguei no lista.c");
    printf("\nid: %d\nproc: %s", id, hist); //ok
    return pac_adicionar_historico(LISTA_buscar(lista, id), hist);
}

bool remover_historico(LISTA* lista, int id){
    return pac_remover_historico(LISTA_buscar(lista, id));
}