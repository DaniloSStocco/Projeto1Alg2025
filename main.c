#include "lista.h"
#include "avl.h"
#include "heap.h"
//#include "fila.h"
//#include "pilha.h"
#include "paciente.h"
#include "IO.h"

int main(){
///////////////////////////////////////////// PROJETO 2 //////////////////////////////////////////////////

    AVL *Ar = avl_criar();//onde os pacientes ficarão armazenados
    HEAP *triagem = heap_criar();

    LOAD(&Ar, &triagem);

    char tempnome[TAM];
    int tempid, tempprio;

    int escolha;
    printf("---SISTEMA DE PRONTO-SOCORRO DO SUS---");
    do{
        printf("\nO que deseja fazer?");
        printf("\n1. Registrar paciente");
        printf("\n2. Remover paciente");
        printf("\n3. Listar pacientes");
        printf("\n4. Buscar pacientes por id");
        printf("\n5. Mostrar fila de espera");
        printf("\n6. Dar alta ao paciente");
        printf("\n7. Sair\n");

        scanf("%d", &escolha);

        switch (escolha)
        {
            case 1: //Registrar Paciente
            {
                printf("\nDigite o id do paciente: ");
                scanf("%d", &tempid);
                if(avl_buscar(Ar, tempid) == NULL){ //nao encontrou 
                    printf("\nDigite o nome do novo paciente: ");
                    getchar();
                    fgets(tempnome, TAM, stdin);
                    tempnome[strcspn(tempnome, "\n")] = '\0';
                    do{
                        printf("\nDigite a prioridade do procedimento (de 1 a 5): ");
                        scanf("%d", &tempprio);
                        if(tempprio <= 0 || tempprio > 5){
                            printf("\nPrioridade invalida, digite novamente.");
                        }
                    }while(tempprio <= 0 || tempprio > 5);

                    PACIENTE *pac = pac_criar(tempnome, tempid, tempprio);
                    avl_inserir(Ar, pac);
                    heap_inserir(triagem, pac);
                }
                else{ //encontrou!!
                    printf("\n O paciente ja existe");
                }
                break;
            }
            case 2: // Remover Paciente
            {
                printf("\nDigite o id do paciente que deseja remover: ");
                scanf("%d", &tempid);
                    if(avl_buscar(Ar, tempid) != NULL){ //encontrou
                        if(heap_buscar(triagem, tempid) == NULL){ //operação O(n) mas que evita um campo a mais na sctruct paciente
                            avl_remover(Ar, tempid);
                        }
                        else{
                            printf("\nO paciente esta em espera na fila, portando nao pode ser removido");
                        }
                    }
                    else{
                        printf("\nPaciente nao encontrado");
                    }
                break;
            }
            case 3: // Listar Pacientes 
            {
                avl_imprimir(Ar);
                break;
            }
            case 4: //Buscar pacientes por id
            {
                printf("\nDigite o id do paciente que deseja buscar: ");
                scanf("%d", &tempid);
                if(avl_buscar(Ar, tempid) != NULL){
                    printf("\nPaciente encontrado:");
                    pac_imprimir(avl_buscar(Ar, tempid), 0);
                }
                else{
                    printf("\nPaciente nao encontrado");
                }
                break;
            }
            case 5: //Mostrar fila de espera
            {
                heap_imprimir(triagem);
                break;
            }
            case 6: //Dar alta ao paciente
            {
                if(!heap_vazia(triagem)){
                    PACIENTE* pac = heap_remover(triagem);
                    printf("\nPaciente liberado:");
                    pac_imprimir(pac, 0);
                }
                break;
            }
            case 7:
            {
                printf("\nSaindo..");
                break;
            }
            default:
                printf("\nEscolha invalida");
                break;
        }
        }
    while(escolha != 7);

    SAVE(Ar, triagem);
}