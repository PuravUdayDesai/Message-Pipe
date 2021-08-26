#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "priority_queue.h"
#include "queue.h"

heap_node *get_last_parent(priority_queue root);
heap_node *get_last_node(priority_queue root);
void heapify(priority_queue *root, heap_node *current_node);
void heapify_rev(heap_node *root);

void init_heap(priority_queue *root)
{
    *root = NULL;
    return;
}

void enqueue_pq(priority_queue *root, priority_node data)
{
    heap_node *new_node = (heap_node *)malloc(sizeof(heap_node));
    if (new_node == NULL)
    {
        return;
    }
    new_node->data.data = data.data;
    new_node->data.priority = data.priority;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    if (*root == NULL)
    {
        *root = new_node;
        return;
    }

    heap_node *last_node = get_last_parent(*root);

    new_node->parent = last_node;
    if (last_node->left == NULL)
    {
        last_node->left = new_node;
    }
    else
    {
        last_node->right = new_node;
    }

    if (data.priority > last_node->data.priority)
    {
        return;
    }

    heapify(root, new_node);

    return;
}

heap_node *get_last_parent(priority_queue root)
{
    queue_list qu;
    init_queue(&qu);

    enqueue_queue(&qu, root);

    heap_node *last_parent = NULL;

    while (!is_queue_empty(qu))
    {
        last_parent = dequeue_queue(&qu);
        if (last_parent != NULL)
        {
            if (last_parent->left != NULL && last_parent->right != NULL)
            {
                enqueue_queue(&qu, last_parent->left);
                enqueue_queue(&qu, last_parent->right);
            }
            else
            {
                break;
            }
        }
    }

    return last_parent;
}

heap_node *get_last_node(priority_queue root)
{
    queue_list qu;
    init_queue(&qu);

    enqueue_queue(&qu, root);

    heap_node *last_node = NULL;

    while (!is_queue_empty(qu))
    {
        last_node = dequeue_queue(&qu);
        if (last_node != NULL)
        {
            if (last_node->left != NULL)
            {
                enqueue_queue(&qu, last_node->left);
            }
            if (last_node->right != NULL)
            {
                enqueue_queue(&qu, last_node->right);
            }
        }
    }

    return last_node;
}

priority_node *denqueue_pq(priority_queue *root)
{
    if (*root == NULL)
    {
        return NULL;
    }

    priority_node *root_data = (priority_node *)malloc(sizeof(priority_node));
    root_data->data = (*root)->data.data;
    root_data->priority = (*root)->data.priority;

    if ((*root)->left == NULL && (*root)->right == NULL)
    {
        free(*root);
        *root = NULL;
        return root_data;
    }

    heap_node *last_node = get_last_node(*root);

    if (last_node == NULL)
    {
        return NULL;
    }

    if (last_node == *root)
    {
        free(*root);
        *root = NULL;
        return NULL;
    }

    (*root)->data = last_node->data;

    heap_node *last_node_parent = last_node->parent;
    if (last_node_parent->left == last_node)
    {
        last_node_parent->left = NULL;
    }
    else
    {
        last_node_parent->right = NULL;
    }
    free(last_node);

    heap_node *guide = *root;

    int temp = 0;

    if (guide->left != NULL && guide->data.priority < guide->left->data.priority &&
        guide->right != NULL && guide->data.priority < guide->right->data.priority)
    {
        return root_data;
    }

    heapify_rev(*root);

    return root_data;
}

void heapify(priority_queue *root, heap_node *current_node)
{
    if (*root == NULL)
    {
        return;
    }
    if (current_node->parent == NULL)
    {
        return;
    }
    if (current_node->data.priority < current_node->parent->data.priority)
    {
        priority_node temp;
        temp = current_node->data;
        current_node->data = current_node->parent->data;
        current_node->parent->data = temp;

        heapify(root, current_node->parent);
    }

    return;
}

void heapify_rev(heap_node *root)
{
    if (root == NULL)
    {
        return;
    }

    heap_node *guide = root;
    priority_node temp;

    if (guide->left != NULL && guide->right != NULL)
    {
        if (guide->left->data.priority < guide->right->data.priority)
        {
            if (guide->data.priority > guide->left->data.priority)
            {
                temp = guide->data;
                guide->data = guide->left->data;
                guide->left->data = temp;

                heapify_rev(guide->left);
            }
        }
        else
        {
            if (guide->data.priority > guide->right->data.priority)
            {
                temp = guide->data;
                guide->data = guide->right->data;
                guide->right->data = temp;

                heapify_rev(guide->right);
            }
        }
    }
    else if (guide->left != NULL && guide->right == NULL)
    {
        if (guide->left->data.priority < guide->data.priority)
        {
            temp = guide->data;
            guide->data = guide->left->data;
            guide->left->data = temp;
        }
    }

    return;
}