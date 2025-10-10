#include <stdio.h>
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "paciente.h"
#include "IO.h"


int main(){
    LISTA *lista_geral = LISTA_criar(false);
    FILA *triagem = FILA_criar();

    int escolha;
    printf("---SISTEMA DE PRONTO-SOCORRO DO SUS---");
    do{
        printf("\nO que deseja fazer?");
        printf("\n1. Registrar paciente");
        printf("\n2. Registrar obito de paciente");
        printf("\n3. Adicionar procedimento ao historico medico");
        printf("\n4. Desfazer procedimento do historico medico");
        printf("\n5. Chamar paciente para atendimento");
        printf("\n6. Mostrar fila de espera");
        printf("\n7. Mostrar histórico do paciente");
        printf("\n8. Sair");

        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            int tempid; 
            printf("\n\nDigite o id desse paciente (crie um se ele nao for registrado):");
            scanf("%d", &tempid);
            if(LISTA_buscar(lista_geral, tempid) != NULL){
                FILA_inserir(triagem ,LISTA_buscar(lista_geral, tempid));
            }
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
            break;
        case 6:
            /* code */
            break;
        case 7:
            /* code */
            break;
        case 8:
            /* code */
            break;

        default:
            break;
        }
    }while(escolha != 8);
}