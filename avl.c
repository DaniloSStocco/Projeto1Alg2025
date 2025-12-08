#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"
#include "paciente.h"
#define max(a,b) ((a > b) ? a : b)

typedef struct no_ NO;

struct no_{
    PACIENTE *pac;
    NO* esq;
    NO* dir;
    int altura;
};

struct avl_{
    NO* raiz;
    int profundidade;
};

AVL* avl_criar(void){
    AVL* T = (AVL*) malloc(sizeof(AVL));
    if(T != NULL) {
        T->raiz = NULL; T->profundidade = -1;
    }
    return T;
}

void avl_apagar_aux(NO* raiz) {
    if(raiz != NULL){
        avl_apagar_aux((raiz)->esq);
        avl_apagar_aux((raiz)->dir);
        pac_apagar(&raiz->pac);
        free(raiz);
    }
}

void avl_apagar(AVL** T){
    avl_apagar_aux((*T)->raiz);
    free(*T);
    *T = NULL;
}

bool avl_vazia(AVL* T){
    if(T->raiz == NULL){
        return(true);

    } else{
        return(false);
    }
}



int avl_altura_no(NO* raiz){
    if(raiz == NULL){
        return -1;
    } else{
        return raiz->altura;
    }
}

NO* avl_cria_no(PACIENTE* pac){
    NO* no = (NO*) malloc(sizeof(NO));
    if(no != NULL) {
        no->altura = 0;
        no->dir = NULL;
        no->esq = NULL;
        no->pac = pac;
    }
    return no;
}

NO *rodar_direita(NO *a) {
    NO* b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) +1;
    return b;
}

NO *rodar_esquerda(NO *a) {
    NO* b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) +1;
    return b;
}

NO *rodar_esquerda_direita(NO *a){
    a->esq = rodar_esquerda(a->esq);
    return rodar_direita(a);
}

NO *rodar_direita_esquerda(NO *a){
    a->esq = rodar_direita(a->dir);
    return rodar_esquerda(a);
}

NO* avl_inserir_no(NO*raiz, PACIENTE* pac){
    if(raiz == NULL){
        raiz = avl_cria_no(pac);
    }
    else if(pac_get_id(pac) < pac_get_id(raiz->pac)){
        raiz->esq = avl_inserir_no(raiz->esq, pac);
    }
    else if(pac_get_id(pac) > pac_get_id(raiz->pac)){
        raiz->dir = avl_inserir_no(raiz->dir, pac);
    }

    raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
    int FB = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);

    if (FB == -2){
        if((avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir)) <= 0){
            raiz = rodar_esquerda(raiz);
        } else{
            raiz = rodar_direita_esquerda(raiz);
        }
    }

    if (FB == 2){
        if((avl_altura_no(raiz->esq->esq) - avl_altura_no(raiz->esq->dir)) >= 0){
            raiz = rodar_direita(raiz);
        } else {
            raiz = rodar_esquerda_direita(raiz);
        }
    }

    return raiz;
}

bool avl_inserir(AVL* T, PACIENTE* pac){
    return((T->raiz = avl_inserir_no(T->raiz, pac)) != NULL);
}

void troca_max_esq(NO *troca, NO* raiz, NO* ant){
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if(raiz == ant){
        ant->esq = troca->esq;
    } else{
        ant->dir = troca->esq;
    }

    PACIENTE* p = raiz->pac;
    raiz->pac = troca->pac;
    pac_apagar(&p);
    free(troca);
    troca = NULL;
}

NO *avl_remover_aux(NO *raiz, int id){
    NO* p;

    if(raiz == NULL){
        return(NULL);
    }
    else if(id == pac_get_id(raiz->pac)){
        if(raiz->esq == NULL || raiz->dir == NULL){
            p = raiz;
            if(raiz->esq == NULL){
                raiz = raiz->dir;
            } else{
                raiz = raiz->esq;
            }
            pac_apagar(&p->pac);
            free(p);
            p = NULL;
        }
        else{
            troca_max_esq(raiz->esq, raiz, (raiz));
        }
    }
    else if(id < pac_get_id(raiz->pac)){
        raiz->esq = avl_remover_aux(raiz->esq, id);
    }
    else if(id > pac_get_id(raiz->pac)){
        raiz->dir = avl_remover_aux(raiz->dir, id);
    }
    if(raiz != NULL){
        raiz->altura = max(avl_altura_no(raiz->esq),avl_altura_no(raiz->dir))+1;
        int FB = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);

        if (FB == -2){
            if((avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir)) <= 0){
                raiz = rodar_esquerda(raiz);
            } else{
                raiz = rodar_direita_esquerda(raiz);
            }
        }

        if (FB == 2){
            if((avl_altura_no(raiz->esq->esq) - avl_altura_no(raiz->esq->dir)) >= 0){
                raiz = rodar_direita(raiz);
            } else {
                raiz = rodar_esquerda_direita(raiz);
            }
        }
    }
    return(raiz);
}

bool avl_remover(AVL *T, int id){
    return((T->raiz = avl_remover_aux(T->raiz, id)) != NULL);
}

PACIENTE* avl_buscar2(NO* raiz, int id){
    if(raiz == NULL){
        return NULL;
    }
    if(id == pac_get_id(raiz->pac)){
        return(raiz->pac);
    }

    if(id < pac_get_id(raiz->pac)){
        return(avl_buscar2(raiz->esq, id));
    } else{
        return(avl_buscar2(raiz->dir, id));
    }
}

PACIENTE* avl_buscar(AVL *T, int id){
    return(avl_buscar2(T->raiz, id));
}