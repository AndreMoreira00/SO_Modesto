#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scheduler.h"
#include "process.h"

int random_time(){
    srand(time(NULL));
    int time = rand()%10;
    return time;
}

int random_class(){
    srand(time(NULL));
    int class = rand()%2;
    printf("%d", class);
}

int main()
{
    int quantum, id = 0, ciclo = 0;
    Scheduler sched;
    Process *p, *proc_it;
    int num_processos = 0;
    int max_processos = 5;
    int processos_ativos = 0;
    srand(time(NULL));
    printf("Defina um Quantum: ");
    scanf("%d", &quantum);
    init_scheduler(&sched, quantum);
    while(ciclo < 30){ 
        printf("\n Ciclo %d\n", ciclo);
        if(num_processos < max_processos && (rand() % 3 == 0)){
            p = create_process(id++, 2 + rand() % 8);
            p->quantum_remaining = quantum;
            add_to_ready_queue(&sched, p);
            printf("Processo criado: ");
            print_process(p);
            num_processos++;
        }
        if(sched.ready_queue != NULL && (rand() % 5 == 0)){
            proc_it = sched.ready_queue->next;
            int bloqueados = 0;
            do{
                if (proc_it->state == PRONTO){
                    proc_it->state = BLOQUEADO;
                    printf("Processo %d BLOQUEADO\n", proc_it->pid);
                    break;
                }
                proc_it = proc_it->next;
            } 
            while(proc_it != sched.ready_queue->next);
        } 
        else if(sched.ready_queue != NULL && (rand() % 5 == 1)){
            proc_it = sched.ready_queue->next;
            do{
                if(proc_it->state == BLOQUEADO){
                    proc_it->state = PRONTO;
                    printf("Processo %d DESBLOQUEADO\n", proc_it->pid);
                    break;
                }
                proc_it = proc_it->next;
            } 
            while (proc_it != sched.ready_queue->next);
        }
        Process *executado = schedule(&sched);
        if(executado != NULL){
            printf("Executando: ");
            print_process(executado);
            if(executado->state == TERMINADO){
                printf("Processo %d TERMINADO\n", executado->pid);
                destroy_process(executado);
                num_processos--;
            }
        } 
        else{
            printf("Nenhum processo pronto para executar.\n");
        }
        printf("Fila de prontos:\n");
        if(sched.ready_queue != NULL)
            print_queue(&sched);
        else
            printf("Fila vazia.\n");
        ciclo++;
    }
    return 0;
}
