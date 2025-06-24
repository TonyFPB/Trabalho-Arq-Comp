#include <stdlib.h>
#include "fila.h"

// Funções de fila
void inicializarFila(Fila *fila) {
    fila->inicio = fila->fim = NULL;
}

void enfileirar(Fila *fila, PCB *processo) {
    Node *novo = malloc(sizeof(Node));
    novo->processo = processo;
    novo->prox = NULL;
    if (fila->fim) fila->fim->prox = novo;
    else fila->inicio = novo;
    fila->fim = novo;
}

PCB* desenfileirar(Fila *fila) {
    if (!fila->inicio) return NULL;
    Node *temp = fila->inicio;
    PCB *proc = temp->processo;
    fila->inicio = temp->prox;
    if (!fila->inicio) fila->fim = NULL;
    free(temp);
    return proc;
}

int filaVazia(Fila *fila) {
    return fila->inicio == NULL;
}
