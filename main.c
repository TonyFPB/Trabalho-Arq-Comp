#include <stdio.h>
#include <unistd.h> // usleep() -> uso de delay
#include <locale.h> // permitir acentua��o
#include <time.h>   

#include "escalonamento.h"

#define DELAY 80000 // Delay padr�o -> 0.08s

int defineDelay(int opcao){
	switch(opcao){
		case 1: // LENTA
			return DELAY*6;
		case 2: 
			return DELAY*3;
		default:
			return DELAY;
	}
}

int main() {
    srand(time(NULL));
	PCB processos[MAX_PROCESSES];
	setlocale(LC_ALL, "Portuguese");
    int n, delaySimulacao;
    
	printf("Informe o n�mero de processos (m�x %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    
	printf("Velocidade da simula��o, digite:\n1 para lenta\n2 para m�dia\n3 para r�pida.\n", MAX_PROCESSES);
    scanf("%d", &delaySimulacao);
    delaySimulacao = defineDelay(delaySimulacao);
    
    if (n > MAX_PROCESSES) n = MAX_PROCESSES;

    for (int i = 0; i < n; i++) {
        processos[i].PID = i + 1;
        processos[i].PPID = 0; // podemos assumir um �nico pai fict�cio
        processos[i].tempo_restante = 20 + rand() % 21; // servi�o entre 20 e 40
        processos[i].status = NOVO;
    }

    simularEscalonador(processos, n, delaySimulacao);
    return 0;
}
