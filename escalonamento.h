#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // usleep() -> uso de delay

#include "fila.h"

#define MAX_PROCESSES 10
#define QUANTUM 5

// Duracao dos I/O
#define IO_DISK 20
#define IO_TAPE 15
#define IO_PRINTER 10

void simularEscalonador(PCB processos[], int n, int delaySimulacao);
void processarIO(Fila *filaIO, Fila *filaDestino, int prioridadeDestino, int tempo, const char* nomeIO);
int sorteiaIO();
