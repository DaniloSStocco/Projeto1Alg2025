#include <stdlib.h>
#include "heap.h"

#define CAPACIDADE_INICIAL 512

struct heap_ {
    PACIENTE **v;
    int tamanho;
    int capacidade;
};

// Comparação fixa, interna — heap de máxima prioridade
int comparar(const PACIENTE *a, const PACIENTE *b) {
    int pa = paciente_get_prioridade(a);
    int pb = paciente_get_prioridade(b);

    if (pa > pb) return 1;
    if (pa < pb) return -1;
    return 0;
}

// função para troca
static void trocar(PACIENTE **a, PACIENTE **b) {
    PACIENTE *tmp = *a;
    *a = *b;
    *b = tmp;
}

static bool aumentar_capacidade(HEAP *h) {
    int nova = h->capacidade * 2;
    PACIENTE **tmp = realloc(h->v, sizeof(PACIENTE*) * nova);
    if (!tmp) return false;

    h->v = tmp;
    h->capacidade = nova;
    return true;
}

void subir(HEAP *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (comparar(h->v[i], h->v[pai]) > 0) {
            trocar(&h->v[i], &h->v[pai]);
            i = pai;
        } else 
            break;
    }
}

void descer(HEAP *h, int i) {
    while (1) {
        int maior = i;
        int esq = 2*i + 1;
        int dir = 2*i + 2;

        if (esq < h->tamanho && comparar(h->v[esq], h->v[maior]) > 0)
            maior = esq;
        if (dir < h->tamanho && comparar(h->v[dir], h->v[maior]) > 0)
            maior = dir;

        if (maior != i) {
            trocar(&h->v[i], &h->v[maior]);
            i = maior;
        } else break;
    }
}
//funcoes do .h
HEAP *heap_criar(void) {
    HEAP *h = malloc(sizeof(HEAP));
    if (!h) return NULL;

    h->v = malloc(sizeof(PACIENTE*) * CAPACIDADE_INICIAL);
    if (!h->v) {
        free(h);
        return NULL;
    }

    h->tamanho = 0;
    h->capacidade = CAPACIDADE_INICIAL;
    return h;
}

void heap_destruir(HEAP *h) {
    if (!h) return;
    free(h->v);
    free(h);
}

// Funcoes do .h
bool heap_vazia(const HEAP *h) {
    return h->tamanho == 0;
}

bool heap_inserir(HEAP *h, PACIENTE *p) {
    if (h->tamanho == h->capacidade) {
        if (!aumentar_capacidade(h)) return false;
    }

    h->v[h->tamanho] = p;
    subir(h, h->tamanho);
    h->tamanho++;
    return true;
}

PACIENTE *heap_remover(HEAP *h) {
    PACIENTE *topo = h->v[0];

    h->tamanho--;

    if (h->tamanho > 0) {
        h->v[0] = h->v[h->tamanho];
        descer(h, 0);
    }

    return topo;
}

PACIENTE *heap_topo(const HEAP *h) {
    if (h->tamanho == 0) return NULL;
    return h->v[0];
}
