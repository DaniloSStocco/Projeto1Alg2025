#define MAX 1020
#include "paciente.h"
#include "pilha.h"
struct paciente_{
    char nome[MAX];
    int id;
    PILHA *pilha;
};

PACIENTE *pac_criar (char nome[],int id){
    PACIENTE *paciente;

    paciente = (PACIENTE*)malloc(sizeof(PACIENTE));

    if (paciente != NULL){
        strcpy(paciente->nome, nome);
        paciente->id = id;
        paciente->pilha = pilha_criar();
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

char *pac_get_nome(PACIENTE* paciente){
    if(paciente != NULL){
        return(paciente->nome);
    }
    printf("Esse paciente não existe");
    return (NULL);
}

PILHA* pac_get_pilha(PACIENTE* paciente){
    if(paciente != NULL){
        return(paciente->pilha);
    }
    printf("Esse paciente não existe");
    return (NULL);
}

PILHA** pac_get_refpilha(PACIENTE* paciente){
    if(paciente != NULL){
        return(&paciente->pilha);
    }
    printf("Esse paciente não existe");
    return (NULL);
}

bool pac_set_nome(PACIENTE* paciente, char nome[]){
    if(paciente != NULL){
        strcpy(paciente->nome, nome);
        return(true);
    }
    printf("Esse paciente não existe");
    return(false);
}

bool pac_adicionar_historico(PACIENTE* paciente, char hist[100]){
    if(paciente != NULL){ //encontrou
        printf("\ncheguei no pac_add_hist e encontrei o %s, que vai fazer um %s", paciente->nome, hist);
        PROCEDIMENTO *proc = criarproc(hist);
        pilha_empilhar(paciente->pilha, proc);
        return(true);
    }
    printf("Esse paciente não existe");
    return(false);
}

bool pac_remover_historico(PACIENTE* paciente){
    if(paciente != NULL){
        pilha_desempilhar(paciente->pilha);
        return(true);
    }
    printf("Esse paciente não existe");
    return(false);
}

void pac_imprimir(PACIENTE* paciente){
    if (paciente != NULL){
        printf("\nNome do paciente: %s\nID do paciente: %d\n", paciente->nome, paciente->id);
    }
    else
        printf("Esse paciente não existe");
}
