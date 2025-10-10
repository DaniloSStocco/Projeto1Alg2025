#ifndef LISTA_H
	#define LISTA_H

	#include "paciente.h"
	#include "item.h"
	                       
	typedef struct lista_ LISTA;

	LISTA *LISTA_criar(bool ordenada);
	bool LISTA_inserir(LISTA *lista, ITEM *item);
	PACIENTE* LISTA_buscar(LISTA *lista, int chave);
	PACIENTE *LISTA_remover(LISTA *lista, int chave);
	//ITEM *LISTA_remover_inicio(LISTA *lista);
	//ITEM *LISTA_remover_fim(LISTA *lista);
	PACIENTE* LISTA_buscar(LISTA *lista, int chave);
	bool LISTA_apagar(LISTA **lista);
	int LISTA_tamanho(LISTA *lista);
	bool LISTA_vazia(LISTA *lista);
	bool LISTA_cheia(LISTA *lista);
	void LISTA_imprimir(LISTA *lista);
	void adicionar_historico(LISTA *lista, int id, char hist[]);
	void remover_historico(LISTA* lista, int id);

#endif