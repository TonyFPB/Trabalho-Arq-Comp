// fila.h

typedef enum {NOVO, PRONTO, EXECUTANDO, ESPERANDO_IO, FINALIZADO} Status;
typedef enum {DISCO, FITA, IMPRESSORA} IOType;

typedef struct PCB {
    int PID;
    int PPID;
    int prioridade; // 0 = alta, 1 = baixa
    Status status;
    int tempo_restante; // serviço
    int io_tempo_restante;
    IOType io_tipo;
} PCB;

typedef struct Node {
    PCB *processo;
    struct Node *prox;
} Node;

typedef struct Fila {
    Node *inicio, *fim;
} Fila;

void inicializarFila(Fila *fila);
void enfileirar(Fila *fila, PCB *processo);
PCB* desenfileirar(Fila *fila);
int filaVazia(Fila *fila);
