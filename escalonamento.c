#include "escalonamento.h"

// Fun��o para simular cria��o aleat�ria de I/O
int sorteiaIO() {
    return rand()%3; // 0 disco, 1 fita, 2 impressora
}

// Simula��o principal
void simularEscalonador(PCB processos[], int n, int delaySimulacao) {
    Fila alta, baixa, io_disco, io_fita, io_impressora;
    inicializarFila(&alta);
    inicializarFila(&baixa);
    inicializarFila(&io_disco);
    inicializarFila(&io_fita);
    inicializarFila(&io_impressora);

    // Todos come�am na fila de alta prioridade
    for (int i = 0; i < n; i++) {
        processos[i].status = PRONTO;
        processos[i].prioridade = 0;
        enfileirar(&alta, &processos[i]);
    }

    int tempo = 0;

    while (1) {
        // Verifica se h� processos a executar
        PCB *proc = NULL;
        if (!filaVazia(&alta)) {
            proc = desenfileirar(&alta);
        } else if (!filaVazia(&baixa)) {
            proc = desenfileirar(&baixa);
        }

        if (proc) {
            proc->status = EXECUTANDO;
            printf("Tempo %d: Executando PID %d (Prioridade %d)\n", tempo, proc->PID, proc->prioridade);

            int tempo_exec = (proc->tempo_restante > QUANTUM) ? QUANTUM : proc->tempo_restante;
            proc->tempo_restante -= tempo_exec;
            tempo += tempo_exec;

            // Ap�s execu��o
            if (proc->tempo_restante == 0) {
                proc->status = FINALIZADO;
                printf("Tempo %d: PID %d finalizado.\n", tempo, proc->PID);
            } else {
                // Simula chance de I/O
                if (rand() % 2 == 0) {
                    proc->status = ESPERANDO_IO;
                    proc->io_tipo = sorteiaIO();
                    switch (proc->io_tipo) {
                        case DISCO:
                            proc->io_tempo_restante = IO_DISK;
                            enfileirar(&io_disco, proc);
                            printf("Tempo %d: PID %d solicitou I/O DISCO.\n", tempo, proc->PID);
                            break;
                        case FITA:
                            proc->io_tempo_restante = IO_TAPE;
                            enfileirar(&io_fita, proc);
                            printf("Tempo %d: PID %d solicitou I/O FITA.\n", tempo, proc->PID);
                            break;
                        case IMPRESSORA:
                            proc->io_tempo_restante = IO_PRINTER;
                            enfileirar(&io_impressora, proc);
                            printf("Tempo %d: PID %d solicitou I/O IMPRESSORA.\n", tempo, proc->PID);
                            break;
                    }
                } else {
                    proc->status = PRONTO;
                    proc->prioridade = 1;
                    enfileirar(&baixa, proc);
                    printf("Tempo %d: PID %d sofreu preemp��o.\n", tempo, proc->PID);
                }
            }
        } else {
            tempo++;
        }

        // Processa I/O
        Node *nodo;
        // Disco
        nodo = io_disco.inicio;
        while (nodo) {
            nodo->processo->io_tempo_restante--;
            if (nodo->processo->io_tempo_restante == 0) {
                PCB *retorno = desenfileirar(&io_disco);
                retorno->status = PRONTO;
                retorno->prioridade = 1;
                enfileirar(&baixa, retorno);
                printf("Tempo %d: PID %d retornou do DISCO.\n", tempo, retorno->PID);
            } else {
                nodo = nodo->prox;
            }
        }
        // Fita
        nodo = io_fita.inicio;
        while (nodo) {
            nodo->processo->io_tempo_restante--;
            if (nodo->processo->io_tempo_restante == 0) {
                PCB *retorno = desenfileirar(&io_fita);
                retorno->status = PRONTO;
                retorno->prioridade = 0;
                enfileirar(&alta, retorno);
                printf("Tempo %d: PID %d retornou da FITA.\n", tempo, retorno->PID);
            } else {
                nodo = nodo->prox;
            }
        }
        // Impressora
        nodo = io_impressora.inicio;
        while (nodo) {
            nodo->processo->io_tempo_restante--;
            if (nodo->processo->io_tempo_restante == 0) {
                PCB *retorno = desenfileirar(&io_impressora);
                retorno->status = PRONTO;
                retorno->prioridade = 0;
                enfileirar(&alta, retorno);
                printf("Tempo %d: PID %d retornou da IMPRESSORA.\n", tempo, retorno->PID);
            } else {
                nodo = nodo->prox;
            }
        }

        // Verifica se todos finalizaram
        int finalizados = 1;
        for (int i = 0; i < n; i++) {
            if (processos[i].status != FINALIZADO) {
                finalizados = 0;
                break;
            }
        }
        
        usleep(delaySimulacao);
        if (finalizados) break;
    }

    printf("Simula��o conclu�da em tempo %d.\n", tempo);
}
