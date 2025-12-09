#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

// Definições de nomes de arquivo
#define ARQUIVO_PACIENTES "pacientes_db.txt"
#define ARQUIVO_FILA "fila_espera.txt"

// Variável estática para auxiliar na escrita dentro do callback da AVL
static FILE *arquivo_saida_global = NULL;

// Função Auxiliar para Callback da AVL 
// Esta função será chamada para cada nó da árvore
void salvar_paciente_no_arquivo(PACIENTE *pac) {
    if (pac != NULL && arquivo_saida_global != NULL) {
        // Formato: ID;PRIORIDADE;NOME (usando ; como separador para facilitar leitura de nomes com espaço)
        fprintf(arquivo_saida_global, "%d;%d;%s\n", 
                pac_get_id(pac), 
                pac_get_prioridade(pac), 
                pac_get_nome(pac));
    }
}

bool SAVE(AVL *lista, HEAP *fila) {
    if (lista == NULL || fila == NULL) return false;

    // 1. Salvar TODOS os pacientes (que estão na AVL)
    arquivo_saida_global = fopen(ARQUIVO_PACIENTES, "w");
    if (arquivo_saida_global == NULL) {
        printf("Erro ao abrir arquivo de pacientes para escrita.\n");
        return false;
    }

    // Percorre a árvore salvando cada paciente
    avl_em_ordem(lista, salvar_paciente_no_arquivo);
    
    fclose(arquivo_saida_global);
    arquivo_saida_global = NULL;

    // 2. Salvar a FILA DE ESPERA (apenas os IDs)
    // Como não podemos acessar o vetor interno da Heap, vamos remover tudo, salvar e re-inserir.
    // Isso mantém o TAD seguro, embora custe um pouco mais de processamento.
    
    FILE *f_fila = fopen(ARQUIVO_FILA, "w");
    if (f_fila == NULL) {
        printf("Erro ao abrir arquivo de fila para escrita.\n");
        return false;
    }

    HEAP *heap_temp = heap_criar();
    if (heap_temp == NULL) {
        fclose(f_fila);
        return false;
    }

    // Esvazia a fila original, escreve no arquivo e guarda no temporário
    while (!heap_vazia(fila)) {
        PACIENTE *p = heap_remover(fila);
        if (p != NULL) {
            fprintf(f_fila, "%d\n", pac_get_id(p)); // Salva apenas o ID
            heap_inserir(heap_temp, p);
        }
    }

    // Devolve os pacientes do temporário para a fila original
    while (!heap_vazia(heap_temp)) {
        PACIENTE *p = heap_remover(heap_temp);
        heap_inserir(fila, p);
    }

    heap_destruir(heap_temp);
    fclose(f_fila);

    printf("\nDados salvos com sucesso.\n");
    return true;
}

bool LOAD(AVL **lista, HEAP **fila) {
    // Aloca as novas estruturas
    *lista = avl_criar();
    *fila = heap_criar();

    if (*lista == NULL || *fila == NULL) return false;

    FILE *f_pac = fopen(ARQUIVO_PACIENTES, "r");
    FILE *f_fila = fopen(ARQUIVO_FILA, "r");

    // Se os arquivos não existirem (primeira execução), não é um erro crítico
    if (f_pac == NULL) {
        if (f_fila) fclose(f_fila); // Fecha o outro se estiver aberto
        return true; // Retorna true assumindo sistema vazio
    }

    // 1. Carregar Pacientes para a AVL
    int id, prio;
    char nome[TAM];
    
    // O formato de leitura deve casar com o fprintf: "%d;%d;%s\n"
    // %[^\n] lê string até encontrar uma quebra de linha
    while (fscanf(f_pac, "%d;%d;%[^\n]\n", &id, &prio, nome) == 3) {
        PACIENTE *novo_pac = pac_criar(nome, id, prio);
        if (novo_pac != NULL) {
            avl_inserir(*lista, novo_pac);
        }
    }
    fclose(f_pac);

    // 2. Carregar a Fila de Espera
    if (f_fila != NULL) {
        while (fscanf(f_fila, "%d", &id) == 1) {
            // Busca o ponteiro do paciente REAL que já está na memória (na AVL)
            PACIENTE *p = avl_buscar(*lista, id);
            
            if (p != NULL) {
                // Insere o mesmo ponteiro na Heap
                heap_inserir(*fila, p);
            }
        }
        fclose(f_fila);
    }

    printf("\nDados carregados com sucesso.\n");
    return true;
}