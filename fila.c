#define MAX_PROCESSES 20

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int id;
  int quantum;
  int remaining;
  int priority;
} Process;

typedef struct{
  Process *queue;
  int lenght; 
  int front;  // quem sai
  int rear;   // quem entra
} ProcessQueue;

void init(ProcessQueue *pq){
  pq->queue = (Process*) malloc(MAX_PROCESSES * sizeof(Process));
  pq->front = pq->rear = -1; 
  pq->lenght = 0;
}

void enqueue(ProcessQueue *pq, Process newProcess){
  //printf("f: %d | r: %d", pq->front, pq->rear);
  if(pq->rear == -1 && pq->front == -1){
    pq->front = 0;
    pq->rear = 1;
    pq->queue[pq->rear] = newProcess;
  }
  else{
    if(pq->rear == pq->front){
      printf("FILA CHEIA!!!\n");
      EXIT_FAILURE;
    }
    else{
      pq->queue[pq->rear] = newProcess;
      pq->rear = (pq->rear+1)%MAX_PROCESSES;
    }
  }
  pq->lenght++;
}

void showQueue(ProcessQueue *pq){
  if(pq->rear == -1){
    printf("Fila vazia!");
    return;
  }
  int k = 0;
  for(int i = pq->rear; k < pq->lenght; ++i, ++k){
    printf("%d ", pq->queue[i].id);
  }
  printf("\n");
}

int main(){
  ProcessQueue q;
  init(&q);
  Process p1;
  p1.id = 1;
  Process p2;
  p2.id = 2;
  Process p3;
  p3.id = 3;
  enqueue(&q, p1);
  enqueue(&q, p2);
  enqueue(&q, p3);
  showQueue(&q);


  return 0;
}