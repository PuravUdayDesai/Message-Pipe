#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void init_queue(queue_list *head)
{
    *head = malloc(sizeof(queue_list));

    (*head)->head = NULL;
    (*head)->rare = NULL;

    return;
}

void enqueue_queue(queue_list *head, heap_node *data)
{
    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));

    if (new_node == NULL)
    {
        return;
    }

    if (data == NULL)
    {
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    queue *guide = *head;

    if (guide->head == NULL && guide->rare == NULL)
    {
        guide->head = new_node;
        guide->rare = new_node;
        return;
    }

    guide->rare->next = new_node;
    guide->rare = new_node;

    return;
}
heap_node *dequeue_queue(queue_list *head)
{
    queue *guide = *head;
    if (guide->head == NULL && guide->rare == NULL)
    {
        return NULL;
    }

    queue_node *current_head = guide->head;

    heap_node *data_current_head = current_head->data;

    guide->head = guide->head->next;

    if (guide->head == NULL)
    {
        guide->rare = NULL;
    }

    free(current_head);

    return data_current_head;
}

int is_queue_empty(queue_list head)
{
    return (head->head == NULL && head->rare == NULL) ? 1 : 0;
}
