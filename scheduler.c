#include "scheduler.h"
#include <stdio.h>

void init_scheduler(Scheduler *sched, int quantum){
  sched->ready_queue = NULL;
  sched->quantum = quantum;
}

void add_to_ready_queue(Scheduler *sched, Process *p){
  if (sched->ready_queue == NULL)
  {
    sched->ready_queue = p;
    p->next = p;
  }else{
    p->next = sched->ready_queue->next;
    sched->ready_queue->next = p;
    sched->ready_queue = p;
  } 
}

Process* schedule(Scheduler *sched){
  // lista vazia
  if (sched->ready_queue == NULL)
  {
    return NULL;
  }
  // pega o proximo processo
  Process *last = sched->ready_queue->next;

  // verifica se todos os processos estao bloqueados e pula eles
  while (last->state == BLOQUEADO){  
    last = sched->ready_queue->next;
    if (last == sched->ready_queue->next)
    {
      return NULL;
    }
  }

  // Coloca o estado e faz os tempos de cada variavel no struct 
  last->state = EXECUTANDO;
  last->total_cpu_time++;
  last->remaining_time--;
  last->quantum_remaining--;

  // verifica se o tempo de excucao ja terminou
  if (last->remaining_time <= 0) {
    last->state = TERMINADO;
    sched->ready_queue->next = last->next;
    if (last == sched->ready_queue) {
      sched->ready_queue = NULL;
    }
    return last;
  }

  // Se o processo nao finalizoi ele volta para a fila de pronto
  if (last->quantum_remaining <= 0) {
    last->quantum_remaining = sched->quantum;
    last->state = PRONTO;
    sched->ready_queue = last;
  }

  // retorna o processo
  return last;
}

void print_queue(const Scheduler *sched){
  Process *last = sched->ready_queue->next;
  do {
      print_process(last);
      last = last->next;
  } while (last != sched->ready_queue->next);
}