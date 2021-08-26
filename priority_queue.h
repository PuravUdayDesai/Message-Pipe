#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

#include "strings.h"

typedef struct priority_node
{
    string data;
    int priority;
} priority_node;

typedef struct heap_node
{
    priority_node data;
    struct heap_node *left;
    struct heap_node *right;
    struct heap_node *parent;
} heap_node;

typedef heap_node *priority_queue;

void init_heap(priority_queue *root);
void enqueue_pq(priority_queue *root, priority_node data);
priority_node *denqueue_pq(priority_queue *root);

#endif