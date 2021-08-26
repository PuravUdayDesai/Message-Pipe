#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED
#define MAX_HASH_SIZE 1024

#include "user.h"

typedef struct hash_table
{
    user arr[MAX_HASH_SIZE];
} hash_table;

int put(hash_table *table, int key, user value);
user *get(hash_table table, int key);
int contains_key(hash_table table, int key);

#endif