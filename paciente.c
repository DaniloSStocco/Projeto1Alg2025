#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "paciente.h"
#define MAX 1020
struct paciente_{
    char nome[MAX];
    int id;
};

PACIENTE *pac_criar (char nome[],int id){
    PACIENTE *paciente;

    paciente = (PACIENTE*)malloc(sizeof(PACIENTE));

    if (paciente != NULL){
        strcpy(paciente->nome, nome);
        paciente->id = id;
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
    printf("Esse paciente não existe");
    return(false);
}

int pac_get_id(PACIENTE* paciente){
    if(paciente != NULL){
        return(paciente->id);
    }
    printf("Esse paciente não existe");
    return (-1);
}

bool pac_set_id(PACIENTE* paciente, int id){
    if(paciente != NULL){
        paciente->id = id;
        return(true);
    }
    printf("Esse paciente não existe");
    return(false);
}

char pac_get_nome(PACIENTE* paciente){
    if(paciente != NULL){
        return(paciente->nome);
    }
    printf("Esse paciente não existe");
    return (-1);
}

bool pac_set_nome(PACIENTE* paciente, char nome[MAX]){
    if(paciente != NULL){
        strcpy(paciente->nome, nome);
        return(true);
    }
    printf("Esse paciente não existe");
    return(false);
}

void pac_imprimir(PACIENTE* paciente){
    if (paciente != NULL){
        printf("\nNome do paciente: %s\nID do paciente: %d\n", paciente->nome, paciente->id);
    }
    printf("Esse paciente não existe");
}