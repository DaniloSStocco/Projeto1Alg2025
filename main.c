#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "paciente.h"
//#include "IO.h"


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
        case 1: //Registrar paciente
        {
            int tempid=0; 
            printf("\n\nDigite o id desse paciente (crie um se ele nao for registrado):");
            scanf("%d", &tempid);
            if(LISTA_buscar(lista_geral, tempid) != NULL){
                FILA_inserir(triagem ,LISTA_buscar(lista_geral, tempid));
            }
            else{
                char tempnome[TAM];
                printf("\nDigite o nome do novo paciente:");
                scanf("%101[^\n]", tempnome);
                PACIENTE *pac = pac_criar(tempnome, tempid);
                LISTA_inserir(lista_geral, pac);
                FILA_inserir(triagem, pac);
            }
            break;}
        case 2: //Registrar obito de paciente
        {
            printf("\nDigite o id do paciente a ser registrado como falecido:");
            int tempid=0;
            scanf("%d", &tempid);
            PACIENTE *pac = LISTA_remover(lista_geral, tempid);
            if(pac != NULL){
                printf("\nO paciente %s, de id %d foi excluido", pac_get_nome(pac), pac_get_id(pac));
            }
            else{
                printf("paciente nao encontrado");
            }
            break;}
        case 3: //Adicionar procedimento ao historico medico
        {
            int tempid=0;
            printf("\nDigite o id do paciente que tera o procedimento registrado:");
            scanf("%d", &tempid);

            char proced[TAM];
            printf("\nEscreva o procedimento:");
            scanf(" %101[^\n]", proced);
            if(adicionar_historico(lista_geral, tempid, proced)){
                printf("\nProcedimento adicionado com sucesso");
            }
            break;}
        case 4: //Desfazer procedimento do historico medico
        {
            int tempid=0;
            printf("\nDigite o id do paciente que tera o procedimento removido:");
            scanf("%d", &tempid);
            if(remover_historico(lista_geral, tempid)){
                printf("\nProcedimento removido com exito");
            }
            else{
                printf("\nErro");
            }
            break;}
        case 5: //Chamar paciente para atendimento
        {
            PACIENTE *pac = FILA_remover(triagem);
            if(pac != NULL){
                printf("\nPaciente %s, favor se dirigir ao guiche 01", pac_get_nome(pac));
            }
            else{
                printf("\nErro na operacao");
            }
            break;}
        case 6: //Mostrar fila de espera
        {
            FILA_imprimir(triagem);
            break;}
        case 7: //Mostrar histórico do paciente
        {
            int tempid=0;
            printf("\nDigite o id do paciente para ver eu historico:");
            scanf("%d", &tempid);
            pilha_imprimir(pac_get_pilha(LISTA_buscar(lista_geral, tempid)));
            break;}
        case 8:
        {
            printf("\nSaindo...");
            break;}

        default:
            break;
        }
    }while(escolha != 8);
}