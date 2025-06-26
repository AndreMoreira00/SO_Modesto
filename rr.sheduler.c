#include "process.h"
#include "rr_scheduler.h"
#include <stddef.h>

// Remove um processoa da fila de prontos
// Retorna 1 se removeu / 0 se não encontrou.
static int remove_from_queue(Scheduler *sched, Process *p)
{
    if (sched->ready_queue == NULL || p == NULL)
    {
        return 0;
    }

    Process *prev = sched->ready_queue;
    while (prev->next != p && prev != sched->ready_queue->next)
    {
        prev = prev->next;
    }

    if (prev->next == p)
    {
        if (p == p->next)
        {
            sched->ready_queue = NULL;
        }
        else
        {
            prev->next = p->next;
            if (sched->ready_queue == p)
            {
                sched->ready_queue = prev;
            }
        }
        p->next = NULL;
        return 1;
    }

    return 0;
}

// Remove um processo bloqueado da fila de prontos
void handle_blocked_process(Scheduler *sched, Process *p)
{
    remove_from_queue(sched, p);
}

// Remove um processo terminado da fila
void handle_terminated_process(Scheduler *sched, Process *p)
{
    if (remove_from_queue(sched, p))
    {
        destroy_process(p);
    }
}