
#ifndef FILA_H
	#define FILA_H
	#include "paciente.h"

	typedef struct fila_ FILA;

	FILA *FILA_criar(void);
	bool FILA_inserir(FILA *fila, PACIENTE *item);
	PACIENTE *FILA_remover(FILA *fila);
	void FILA_apagar(FILA **fila);
	PACIENTE *FILA_frente(FILA *fila);
	int FILA_tamanho(FILA *fila);
	bool FILA_vazia(FILA *fila);
	bool FILA_cheia(FILA *fila);
	bool FILA_imprimir(FILA *f);
	PACIENTE *FILA_buscar(FILA *fila, int id);

	  
#endif
