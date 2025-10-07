#ifndef PACIENTE_H
	#define PACIENTE_H
	
	#include <stdbool.h>
	
	typedef struct paciente_ PACIENTE;
	
	PACIENTE* pac_criar(char nome[],int id);
	bool pac_apagar(PACIENTE**paciente);
	void pac_imprimir(PACIENTE*paciente);
	int pac_get_id(PACIENTE*paciente);
	bool pac_set_id(PACIENTE*paciente, int id);

#endif	
	