#ifndef PROCEDIMENTO_H
    #define PROCEDIMENTO_H

    typedef struct procedimento_ PROCEDIMENTO;

    PROCEDIMENTO* criarproc(char conteudo[]);
    bool apagarproc(PROCEDIMENTO** procedimento);
    void imprimirproc(PROCEDIMENTO* procedimento);
    int contproc(PROCEDIMENTO* procedimento);

#endif