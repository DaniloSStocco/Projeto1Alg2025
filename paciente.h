#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct paciente_ PACIENTE;
typedef struct pilha_ PILHA;  // forward declaration

PACIENTE* pac_criar(char nome[],int id);
bool pac_apagar(PACIENTE** paciente);
void pac_imprimir(PACIENTE* paciente);
int pac_get_id(PACIENTE* paciente);
bool pac_set_id(PACIENTE* paciente, int id);
char* pac_get_nome(PACIENTE* paciente);
bool pac_set_nome(PACIENTE* paciente, char nome[]);
PILHA* pac_get_pilha(PACIENTE* paciente);
PILHA** pac_get_refpilha(PACIENTE* paciente);
bool pac_adicionar_historico(PACIENTE* paciente, char hist[100]);
bool pac_remover_historico(PACIENTE* paciente);

#endif