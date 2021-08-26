#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "priority_queue.h"

typedef struct queue_node
{
    heap_node *data;
    struct queue_node *next;

} queue_node;

typedef struct queue
{

    queue_node *head;
    queue_node *rare;

} queue;

typedef queue *queue_list;

void init_queue(queue_list *head);
void enqueue_queue(queue_list *head, heap_node *data);
heap_node *dequeue_queue(queue_list *head);
int is_queue_empty(queue_list head);

#endif
