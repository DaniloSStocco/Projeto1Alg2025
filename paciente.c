#define MAX 1020
#include "paciente.h"
#include "pilha.h"
struct paciente_{
    char nome[MAX];
    int id;
    int prioridade;
};

PACIENTE *pac_criar (char nome[],int id, int prior){
    PACIENTE *paciente;

    paciente = (PACIENTE*)malloc(sizeof(PACIENTE));

    if (paciente != NULL){
        strcpy(paciente->nome, nome);
        paciente->id = id;
        paciente->prioridade = prior;
        //paciente->pilha = pilha_criar();
        return (paciente);
    }
    printf("Memória cheia, não foi possível adicionar esse paciente");
    return (NULL);
}

bool pac_apagar (PACIENTE **paciente){
    if(paciente != NULL){
        free(*paciente);
        *paciente = NULL;
        return(true);
    }
    printf("Esse paciente nao existe");
    return(false);
}

int pac_get_id(PACIENTE* paciente){
    if(paciente != NULL){
        return(paciente->id);
    }
    printf("Esse paciente nao existe");
    return (-1);
}

bool pac_set_id(PACIENTE* paciente, int id){
    if(paciente != NULL){
        paciente->id = id;
        return(true);
    }
    printf("Esse paciente nao existe");
    return(false);
}

int pac_get_prioridade(PACIENTE* paciente){
    if(paciente != NULL){
        return(paciente->prioridade);
    }
    printf("Esse paciente nao existe");
    return (-1);
}

bool pac_set_prioridade(PACIENTE* paciente, int prior){
    if(paciente != NULL){
        paciente->prioridade = prior;
        return(true);
    }
    printf("Esse paciente nao existe");
    return(false);
}

char *pac_get_nome(PACIENTE* paciente){
    if(paciente != NULL){
        return(paciente->nome);
    }
    printf("Esse paciente nao existe");
    return (NULL);
}

bool pac_set_nome(PACIENTE* paciente, char nome[]){
    if(paciente != NULL){
        strcpy(paciente->nome, nome);
        return(true);
    }
    printf("Esse paciente nao existe");
    return(false);
}
void pac_imprimir(PACIENTE* paciente, int comprioridade){
    if (paciente != NULL){
        if(!comprioridade)
            printf("\nNome do paciente: %s\nID do paciente: %d\n", paciente->nome, paciente->id);
        else
            printf("\nNome do paciente: %s\nID do paciente: %d\nPrioridade do paciente: %d\n", paciente->nome, paciente->id, paciente->prioridade);
    }
    else
        printf("Esse paciente não existe");
}
