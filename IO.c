#include "IO.h"
#include <stdio.h>
#include <stdlib.h>

bool SAVE(LISTA *lista, FILA *fila) {
    if (!lista || !fila)
        return false;

    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    FILE *fp_fila = fopen("fila_pacientes.bin", "wb");
    if (!fp_lista || !fp_fila) {
        if (fp_lista) fclose(fp_lista);
        if (fp_fila) fclose(fp_fila);
        return false;
    }

    // --- Salvando pacientes da lista ---
    int qtdPacientes = LISTA_tamanho(lista);
    fwrite(&qtdPacientes, sizeof(int), 1, fp_lista);

    LISTA *tempLista = LISTA_criar(false); // para restaurar depois

    PACIENTE *pac = LISTA_remover_inicio(lista);
    while (pac != NULL) {
        int id = pac_get_id(pac);
        char nome[TAM];
        strcpy(nome, pac_get_nome(pac));

        fwrite(&id, sizeof(int), 1, fp_lista);
        fwrite(nome, sizeof(char), TAM, fp_lista);

        // salvar o histórico (pilha)
        PILHA *hist = pac_get_pilha(pac);
        int qtdHist = pilha_tamanho(hist);
        fwrite(&qtdHist, sizeof(int), 1, fp_lista);

        PILHA *temp = pilha_criar();
        while (!pilha_vazia(hist)) {
            PROCEDIMENTO *proc = pilha_desempilhar(hist);
            char conteudo[TAM];
            strcpy(conteudo, proc_get_conteudo(proc));
            fwrite(conteudo, sizeof(char), TAM, fp_lista);
            pilha_empilhar(temp, proc);
        }

        // restaura a pilha original
        while (!pilha_vazia(temp))
            pilha_empilhar(hist, pilha_desempilhar(temp));
        pilha_apagar(&temp);

        // guarda o paciente na lista temporária pra restaurar depois
        LISTA_inserir(tempLista, pac);

        pac = LISTA_remover_inicio(lista);
    }

    // restaurar a lista original
    pac = LISTA_remover_inicio(tempLista);
    while (pac != NULL) {
        LISTA_inserir(lista, pac);
        pac = LISTA_remover_inicio(tempLista);
    }
    LISTA_apagar(&tempLista);

    // --- Salvando fila ---
    int qtdFila = FILA_tamanho(fila);
    fwrite(&qtdFila, sizeof(int), 1, fp_fila);

    FILA *tempFila = FILA_criar();
    PACIENTE *pf = FILA_remover(fila);
    while (pf != NULL) {
        int id = pac_get_id(pf);
        fwrite(&id, sizeof(int), 1, fp_fila);
        FILA_inserir(tempFila, pf);
        pf = FILA_remover(fila);
    }

    // restaurar fila original
    pf = FILA_remover(tempFila);
    while (pf != NULL) {
        FILA_inserir(fila, pf);
        pf = FILA_remover(tempFila);
    }
    FILA_apagar(&tempFila);

    fclose(fp_lista);
    fclose(fp_fila);
    return true;
}

bool LOAD(LISTA **lista, FILA **fila) {
    if (!lista || !fila)
        return false;

    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    FILE *fp_fila = fopen("fila_pacientes.bin", "rb");
    if (!fp_lista || !fp_fila) {
        if (fp_lista) fclose(fp_lista);
        if (fp_fila) fclose(fp_fila);
        return false;
    }

    // --- Carregar lista ---
    int qtdPacientes;
    fread(&qtdPacientes, sizeof(int), 1, fp_lista);

    for (int i = 0; i < qtdPacientes; i++) {
        int id;
        char nome[TAM];
        fread(&id, sizeof(int), 1, fp_lista);
        fread(nome, sizeof(char), TAM, fp_lista);

        PACIENTE *pac = pac_criar(nome, id);

        int qtdHist;
        fread(&qtdHist, sizeof(int), 1, fp_lista);

        for (int j = 0; j < qtdHist; j++) {
            char conteudo[TAM];
            fread(conteudo, sizeof(char), TAM, fp_lista);
            PROCEDIMENTO *proc = criarproc(conteudo);
            pilha_empilhar(pac_get_pilha(pac), proc);
        }

        LISTA_inserir(*lista, pac);
    }

    // --- Carregar fila ---
    int qtdFila;
    fread(&qtdFila, sizeof(int), 1, fp_fila);

    for (int i = 0; i < qtdFila; i++) {
        int id;
        fread(&id, sizeof(int), 1, fp_fila);
        PACIENTE *pac = LISTA_buscar(*lista, id);
        if (pac)
            FILA_inserir(*fila, pac);
    }

    fclose(fp_lista);
    fclose(fp_fila);
    return true;
}