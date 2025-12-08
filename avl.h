#ifndef AVL_H
    #define AVL_H
    #define max(a,b) ((a > b) ? a : b)

    #include "paciente.h"
    #include <stdbool.h>
    

    typedef struct avl_ AVL;

    AVL *avl_criar(void);
    bool avl_inserir(AVL *T, PACIENTE *pac);
    PACIENTE* avl_buscar(AVL *T, int id);
    bool avl_remover(AVL *T, int id);
    int avl_altura_no(NO* raiz);
    bool avl_vazia(AVL* T);

#endif