#include "fila.h"
#include "paciente.h"
#define TAM_MAX 50

struct fila_{
    PACIENTE *filapacs[TAM_MAX];
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

bool FILA_inserir(FILA *fila, PACIENTE *pac){
    if(fila != NULL ){
        if(!FILA_cheia(fila)){
            fila->filapacs[fila->fim] = pac;
            fila->fim = (fila->fim+1)%TAM_MAX;
            fila->tamanho++;

            return(true); 
        }
        //printf("\nFalha na operacao: Fila cheia!");
    }
        //printf("\nFila não existe!")
    return(false);
}

PACIENTE *FILA_remover(FILA *fila){
    if(fila != NULL){
        if(!FILA_vazia(fila)){
            PACIENTE *p = fila->filapacs[fila->inicio];
            fila->filapacs[fila->inicio] = NULL;
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
        return(-1);
    }
}

bool FILA_imprimir(FILA *f) {
    if (f == NULL || f->tamanho == 0) {
        printf("\nA fila esta vazia ou nao existe.\n");
        return false;
    }

    printf("\n--- Fila de Pacientes ---\n");

    int cont = f->inicio;
    int i = 0;

    while (i < f->tamanho) {
        pac_imprimir(f->filapacs[cont]);
        cont = (cont + 1) % TAM_MAX;
        i++;
    }

    printf("\n--------------------------");
    return true;
}

PACIENTE *FILA_buscar(FILA *fila, int id) {
    if(fila == NULL || fila->tamanho == 0) {
        return NULL; // fila vazia ou inexistente
    }

    int cont = fila->inicio;
    for(int i = 0; i < fila->tamanho; i++) {
        PACIENTE *p = fila->filapacs[cont];
        if(p != NULL && pac_get_id(p) == id) {
            return p; // paciente encontrado
        }
        cont = (cont + 1) % TAM_MAX;
    }

    return NULL; // paciente não encontrado
}
void FILA_apagar(FILA **fila) {
    if (fila == NULL || *fila == NULL)
        return;

    // Limpa os ponteiros da fila (não apaga os pacientes)
    for (int i = 0; i < (*fila)->tamanho; i++) {
        (*fila)->filapacs[i] = NULL;
    }

    // Libera a estrutura da fila
    free(*fila);
    *fila = NULL;
}