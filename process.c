#include "process.h"  
#include <stdio.h>
#include <stdlib.h>
 
Process* create_process(int pid, int total_time){
    Process *new_process = (Process*) malloc(sizeof(Process));
    if(new_process == NULL){
        printf("Nao foi possivel alocar memoria");
        return NULL; 
    }
    new_process->pid = pid;                
    new_process->total_cpu_time = 0;        
    new_process->remaining_time = total_time; 
    new_process->state = PRONTO;            
    new_process->quantum_remaining = 0;    
    new_process->next = NULL;               
    return new_process;
}

void destroy_process(Process *p){
    if(p != NULL){
        free(p);
    }
}

void print_process(const Process *p){
    if(p == NULL){
        printf("Processo e nulo\n");
        return;
    }
    printf("PID: %d, estado: %d, Tempo restante: %d, Quantum: %d\n", 
           p->pid, p->state, p->remaining_time, p->quantum_remaining);
}