#include <stdio.h>
#include <unistd.h> // usleep() -> uso de delay
#include <locale.h> 
#include <time.h>   

#include "escalonamento.h"

#define DELAY 80000 // Delay padrão -> 0.08s

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
    
	printf("Informe o número de processos (máx %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    
	printf("Velocidade da simulação, digite:\n- 1 para lenta\n- 2 para média\n- 3 para rápida\n-> ");
    scanf("%d", &delaySimulacao);
    delaySimulacao = defineDelay(delaySimulacao);
    
    if (n > MAX_PROCESSES) n = MAX_PROCESSES;

    for (int i = 0; i < n; i++) {
        processos[i].PID = i + 1;
        processos[i].PPID = 0; // podemos assumir um único pai fictício
        processos[i].tempo_restante = 20 + rand() % 21; // serviço entre 20 e 40
        processos[i].status = NOVO;
    }

    simularEscalonador(processos, n, delaySimulacao);
    return 0;
}
