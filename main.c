#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "paciente.h"
#include "IO.h"

int main(){
    LISTA *lista_geral = LISTA_criar(false);
    FILA *triagem = FILA_criar();

    LOAD(&lista_geral, &triagem);

    char tempnome[TAM];
    int tempid;
    char proced[TAM];

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
        printf("\n7. Mostrar historico do paciente");
        printf("\n8. Sair\n");

        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1: //Registrar paciente
        {
            fflush(stdin);
            //int tempid=0; 
            printf("\n\nDigite o id desse paciente (crie um se ele nao for registrado): ");
            scanf("%d", &tempid);

            if(LISTA_buscar(lista_geral, tempid) != NULL){ //encontrou alguem na lista
                if(FILA_buscar(triagem ,tempid) != NULL){ //encontrou esse alguem na fila!!
                    printf("\nO paciente ja esta na fila");
                }
                else{
                FILA_inserir(triagem ,LISTA_buscar(lista_geral, tempid));}
            }
            else{
                //char tempnome[TAM];
                getchar();
                printf("\nDigite o nome do novo paciente: ");
                fgets(tempnome, TAM, stdin);
                tempnome[strcspn(tempnome, "\n")] = '\0';

                PACIENTE *pac = pac_criar(tempnome, tempid);
                LISTA_inserir(lista_geral, pac);
                FILA_inserir(triagem, pac);
            }
            break;}
        case 2: //Registrar obito de paciente
        {
            printf("\nDigite o id do paciente a ser registrado como falecido:");
            tempid=0;
            scanf("%d", &tempid);
            if(FILA_buscar(triagem ,tempid) != NULL){
                printf("\nO paciente nao pode morrer, pois esta na fila");
            }
            else{
                PACIENTE *pac = LISTA_remover(lista_geral, tempid);
            if(pac != NULL){
                printf("\nO paciente %s, de id %d foi excluido", pac_get_nome(pac), pac_get_id(pac));
            }
            else{
                printf("paciente nao encontrado");
            }
            }
            
            break;}
        case 3: //Adicionar procedimento ao historico medico
        {
            tempid=0;
            printf("\nDigite o id do paciente que tera o procedimento registrado:");
            scanf("%d", &tempid);

            //char proced[TAM];
            printf("\nEscreva o procedimento: ");
            getchar();
            fgets(proced, TAM, stdin);
                proced[strcspn(proced, "\n")] = '\0';
            if(adicionar_historico(lista_geral, tempid, proced)){
                printf("\nProcedimento adicionado com sucesso");
            }
            else{
                printf("\nErro na operacao");
            }
            break;}
        case 4: //Desfazer procedimento do historico medico
        {
            tempid=0;
            printf("\nDigite o id do paciente que tera o procedimento removido: ");
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
            tempid=0;
            printf("\nDigite o id do paciente para ver seu historico: ");
            getchar();
            scanf("%d", &tempid);
            pilha_imprimir(pac_get_pilha(LISTA_buscar(lista_geral, tempid)));
            break;}
        case 8:
        {
            printf("\nSaindo...");
            break;}

        default:
            printf("\nEscolha invalida");
            break;
        }
    }while(escolha != 8);

    SAVE(lista_geral, triagem);

}