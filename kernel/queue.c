#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "spinlock.h"
#include "proc.h"

void
queue_push(struct Queue* queue, struct proc* element)
{
	if(queue->size == NPROC)
		panic("max allowable processes reached\n");
	queue->content[queue->tail] = element;
	queue->tail++;
	if(queue->tail == NPROC+1)
	{queue->tail = 0;}
	queue->size++;	
}

void
queue_pop(struct Queue* queue)
{
	if(queue->size == 0)
		{panic("trying to pop from alr empty queue");}
	queue->head++;
	if(queue->head == NPROC+1)
		queue->head = 0;
	queue->size--;
}

struct proc*
queue_front(struct Queue* queue)
{
	if(queue->size == 0)
		return 0;
	return queue->content[queue->head];
}

void 
queue_remove(struct Queue* queue, int pid)
{
	if(queue->size <= 0){return;}
	for(int i = queue->head; i != queue->tail; i= (i+1)%(NPROC+1))
	{
		if(queue->content[i]->pid == pid)
		{
			struct proc* swapper = queue->content[i];
			queue->content[i] = queue->content[(i+1)%(NPROC+1)];
			queue->content[(i+1)%(NPROC+1)] = swapper;
		}
	}
	queue->tail--;
	if(queue->tail < 0){queue->tail = NPROC;}
	queue->size --;
}