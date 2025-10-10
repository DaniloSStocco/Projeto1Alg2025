#ifndef PROCEDIMENTO_H
    #define PROCEDIMENTO_H

    typedef struct procedimento_ PROCEDIMENTO;

    PROCEDIMENTO* criarproc(char conteudo[]);
    bool apagarproc(PROCEDIMENTO** procedimento);
    void imprimirproc(PROCEDIMENTO* procedimento);
    int contproc(PROCEDIMENTO* procedimento);
    char* proc_get_conteudo(PROCEDIMENTO* proc);
    bool proc_set_conteudo(PROCEDIMENTO* proc, char cont[]);

#endif