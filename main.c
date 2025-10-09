#include <stdio.h>
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "paciente.h"
#include "IO.h"
#include "historico.h"


int main(){
    int escolha;
    printf("---SISTEMA DE PRONTO-SOCORRO DO SUS---");
    do{
        printf("\nO que deseja fazer?");
        printf("\n1. Registrar paciente");
        printf("\n2. Registrar óbito de paciente");
        printf("\n3. Adicionar procedimento ao histórico médico");
        printf("\n4. Desfazer procedimento do histórico médico");
        printf("\n5. Chamar paciente para atendimento");
        printf("\n6. Mostrar fila de espera");
        printf("\n7. Mostrar histórico do paciente");
        printf("\n8. Sair");

        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            /* code */
            break;
        
        default:
            break;
        }
    }while(escolha != 8);
}