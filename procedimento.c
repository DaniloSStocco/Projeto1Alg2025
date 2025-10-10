#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "procedimento.h"

struct procedimento_ {
    char conteudo[100];
};//Struct do procedimento, contendo uma string de, no máximo, 100 caracteres (tamanho máximo do histórico)

PROCEDIMENTO* criarproc(char conteudo[]){
    PROCEDIMENTO* procedimento;

    procedimento = (PROCEDIMENTO*) malloc(sizeof(PROCEDIMENTO));
    if (procedimento != NULL){
        strcpy(conteudo,procedimento->conteudo);
        return(procedimento);
    }
    printf("\nNão foi possível criar esse procedimento, memória cheia\n");
    return(NULL);
}//Cria um procedimento

bool apagarproc(PROCEDIMENTO** procedimento){
    if(*procedimento != NULL){
        free (*procedimento);
        *procedimento = NULL;
        return(true);
    }
    printf("\nEsse procedimento já havia sido apagado ou não existe\n");
    return(false);
}//Apaga o procedimento

void imprimirproc(PROCEDIMENTO* procedimento){
    if(procedimento != NULL){
        printf("\nProcedimento: %s", procedimento->conteudo);
    }
    printf("Esse procedimento não existe");
}//Imprime o procedimento

int contproc(PROCEDIMENTO* procedimento){
    if(procedimento != NULL){
        return(strlen(procedimento->conteudo));
    }
    printf("Esse procedimento não existe");
    return(-1);
}//Função para contar a quantidade de caracteres do procedimento, a fim de usar essa informação e manter o tamanho
//máximo de caracteres no histórico

char* proc_get_conteudo(PROCEDIMENTO* proc){
    if(proc != NULL){
        return(proc->conteudo);
    }
    return("\nNao encontrado");
}

bool proc_set_conteudo(PROCEDIMENTO* proc, char cont[]){
    if(proc != NULL){
        strcpy(proc->conteudo, cont);
        return(true);
    }
    return(false);
}