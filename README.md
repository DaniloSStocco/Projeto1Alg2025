# Relatório - Trabalho 1 - Pronto Socorro SUS

Alunos: Danilo Salmen Stocco e André Luiz Sousa Paião
N° USP: 16861501 e 16854281


Funcionamento e funcionalidade

O sistema criado neste projeto tem como funcionalidade atuar como uma estrutura de dados e organizador dos mesmos para o sistema de pronto socorro do SUS (Sistema Único de Saúde). Ele organiza os pacientes em listas, cria as filas de atendimento, e mantém um histórico de seus procedimentos médicos. Todo paciente permanece no histórico até eventualmente vir a óbito.

Ele funciona utilizando diversos TADs, como pilhas, listas, filas, e outros que representam dados como os pacientes e os procedimentos, para facilitar o uso dos primeiros nesse gerenciamento. Além disso, possui uma interface (no programa principal, ou “main”) que tem diversas opções para quem estiver o operando.

Além de tudo isso, esse sistema utiliza uma IO para que haja uma permanência de dados no disco rígido do banco de dados do hospital, a fim de que se um paciente voltar ao pronto socorro futuramente, já haverá dados seus no sistema.

Imagem ilustrativa das estruturas de dados utilizadas

Explicações e justificativas

Aqui será explicado e justificado as escolhas, eficiência e adequação das estruturas de dados utilizadas nesse projeto, bem como suas operações.

TAD Paciente: Esse TAD foi feito usando como base o TAD item, de modo que servisse como um tipo de dado “encapsulado” para ser manipulado pela lista e pela fila. Dentro dele, há 3 componentes, que são seu nome (string), seu ID (int) e uma pilha (do tipo ponteiro para PILHA).

Possui funções usuais do TAD item, como criar, apagar, retornar ID, mudar o ID, imprimir , bem como alguns mais específicos para sua condição, como retornar nome (feito usando um ponteiro para char), retornar a pilha (de modo semelhante ao anterior), retornar um ponteiro para a pilha, mudar o nome, criar um procedimento (para ser adicionado ao histórico), remover um procedimento do histórico.

Nessa implementação, o histórico (que é a pilha) faz parte de cada paciente, de modo que já é integrado a cada um individualmente, bem como seus procedimentos.

TAD Lista: Esse TAD lista foi implementado no modelo de lista duplamente encadeada, de modo a poder ser ajustada em tamanho de acordo com a demanda do número de pacientes. Por ser encadeada, seu tamanho máximo apenas depende da memória dos servidores do hospital, conforme especificações.

A lista foi feita de forma duplamente encadeada para que a remoção de pacientes seja feita com mais facilidade, uma vez que não é necessário o uso do nó auxiliar, além de permitir possíveis futuras implementações que dependam de percorrer a lista de trás para frente.

Usa nós que contém os TAD pacientes e ponteiros para o próximo e anterior, e em sua struct possui ponteiro para o início e fim, um inteiro para o tamanho e um booleano para determinar se é uma lista ordenada ou não.

Possui as funções usuais de uma lista duplamente encadeada, como criação, esvaziamento, checagem de lista vazia, apagar a lista, inserir um paciente no início, inserir no fim, busca e remoção (feitos com uma chave, a qual é o ID dos pacientes). Além desses, possuí também operações de adição e remoção de procedimentos no histórico dos pacientes presentes na lista. Isso pois tais operações enviam apenas o id do paciente para fazer a adição ou remoção, de modo que o uso da função na lista permita que a busca ocorra internamente.

TAD Fila: Esse TAD foi implementado no modelo sequencial circular, de modo a ter um tamanho máximo fixo, que nesse caso foi escolhido como 50 pacientes, já que a fila tem tamanho finito.

Foi feito sequencialmente devido ao fato de ter um tamanho finito, além de utilizar a forma circular para manter as inserções e remoções (que são frequentes) em complexidade O(1).

Contém em sua estrutura um vetor de ponteiros para pacientes (de tamanho máximo 50, como dito anteriormente), além de inteiros que guardam a posição inicial e final do vetor, e outro inteiro que guarda o seu tamanho. 

Suas operações são as usuais de um TAD lista, como criação, checagem de fila cheia, checagem de fila vazia, inserção e remoção (beneficiados pelo formato circular), retorno do tamanho, impressão e busca.

Vale lembrar também que suas inserções (feitas no final) e remoções (feitas no começo), típicas de fila, foram usadas para a fila de pacientes justamente em função da especificação, que demandou um modelo FIFO (First in, First out/Primeiro que chegar, primeiro a sair).

TAD Procedimento: Esse TAD foi, de modo semelhante ao paciente, feito com base no TAD item, feito para guardar cada procedimento individualmente e servir como base do tipo de dado que o histórico guarda. Ele guarda os procedimentos médicos de um paciente, individualmente (ou seja, cada procedimento guarda uma instrução médica que o paciente recebeu).

Ele contém apenas um dado, que é seu conteúdo, uma string de no máximo 100 caracteres, de acordo com a especificação. Possui operações similares ao TAD item, como criação, apagar procedimento, imprimir, contar a quantidade de caracteres, retorno do conteúdo e mudança no conteúdo.


TAD Pilha: O TAD pilha (utilizado nesse projeto como o histórico) foi implementado de modo encadeado, a fim de se modificar melhor devido ao alto número de inserções e remoções que receberia.

Mesmo tendo sido feito de modo encadeado, ainda possui um tamanho máximo, que foi determinado pelas especificações como 10 (nesse caso 10 procedimentos), mas por isso possui nós, os quais são formados por um ponteiro para um TAD procedimento, e um ponteiro para o anterior. Enquanto isso, a pilha em si possuí um ponteiro para o nó do topo, e um inteiro que guarda o seu tamanho.

Suas operações são as usuais de uma pilha, como criação, apagar a pilha, verificação de pilha vazia, verificação de pilha cheia, retorno do tamanho, retorno do procedimento mais ao topo, empilhar, desempilhar e imprimir.

Foi implementado como parte do TAD paciente, para que cada um tivesse o histórico próprio. Dessa forma também é garantido que cada histórico é ligado a um paciente por meio de estar presente já na própria struct do TAD paciente, em vez de haver alguma ligação externa.

TAD IO: O TAD IO consiste apenas nas funções SAVE e LOAD, as quais são responsáveis pela permanência de dados. No caso do sistema do Pronto Socorro, as estruturas Lista e Fila são salvas e guardadas em arquivos .bin por meio de manipulação de arquivos. Nota-se que ambas as estruturas guardam os chamados Pacientes, os quais podem ter, individualmente, pilhas armazenando seus procedimentos, tornando o salvamento de tais informações em arquivos desafiadora.

Conclusão

Desse modo, foi feito um sistema que utiliza TADs de forma otimizada e eficiente, além de eficaz. Cada TAD foi feito com base nas demandas e especificações, procurando otimizar a organização da memória e a complexidade dos procedimentos, levando em conta operações como a busca, inserção e remoção. Além disso, foi feito um programa para permitir a persistência dos dados, de modo que a cada execução do programa, sejam gravados os dados na memória do banco de dados do hospital.

Códigos .c, .h, Makefile presentes no .zip contendo esse readme.

Todos os códigos foram feitos com auxílio de slides do professor Dr. Rudinei Goularte seguindo os critérios propostos pelo trabalho e de inteligência artificial.

Versão no PDF disponível também nesse mesmo .zip.