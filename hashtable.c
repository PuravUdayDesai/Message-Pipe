#include <stdlib.h>
#include "hashtable.h"

int put(hash_table *table, int key, user value)
{
    if (key > MAX_HASH_SIZE || key < 0)
    {
        return 0;
    }

    table->arr[key] = value;

    return 1;
}

user *get(hash_table table, int key)
{
    if (key > MAX_HASH_SIZE || key < 0)
    {
        return NULL;
    }

    user *value = (user *)malloc(sizeof(user));
    value->ip_address = table.arr[key].ip_address;
    value->mac_address = table.arr[key].mac_address;
    value->user_name = table.arr[key].user_name;

    return value;
}

int contains_key(hash_table table, int key)
{
    if (key > MAX_HASH_SIZE || key < 0)
    {
        return 0;
    }

    if (get_string(table.arr[key].user_name) != NULL)
    {
        return 1;
    }

    return 0;
}