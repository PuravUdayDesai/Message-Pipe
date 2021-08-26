#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "strings.h"
void init_string(string *str)
{
    str->data = NULL;
    str->size = -1;
    return;
}

void set_string(string *str, char *data)
{
    if (str->data != NULL)
    {
        return;
    }
    int length = strlen(data);
    int size = ceil(length / 8.0);
    size = size <= 0 ? 1 : (length % 8 == 0) ? size + 1
                                             : size;
    str->size = size;
    str->data = (char **)malloc(sizeof(char *) * size);
    for (int i = 0; i < size; i++)
    {
        str->data[i] = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
    }

    int str_i = 0;
    int str_j = 0;
    for (int i = 0; i < length; i++)
    {
        if (i % 8 == 0 && i != 0)
        {
            str_i++;
            str_j = 0;
        }
        str->data[str_i][str_j] = data[i];
        str_j++;
    }
    while (str_i < size)
    {
        if (str_j > 7)
        {
            str_j = 0;
            str_i++;
        }
        else
        {
            for (int i = str_j; i < 8; i++)
            {
                str->data[str_i][i] = '\0';
            }
        }
        str_i++;
    }
    return;
}

void append_string(string *str, char *data)
{
    if (str->data == NULL)
    {
        return;
    }
    int current_length = strlen(data);
    int prev_length = string_length(*str);
    int balance = prev_length % 8;
    if (balance + current_length < 8 && current_length < 8)
    {
        int index = 0;
        for (int i = balance; i < (balance + current_length); i++)
        {
            str->data[str->size - 1][i] = data[index];
            index++;
        }
    }
    else
    {
        int additional_length = current_length - (7 - balance);
        int size = ceil(additional_length / 8.0);
        size = size <= 0 ? 1 : (additional_length % 8 == 0) ? size + 1
                                                            : size;
        int prev_size = str->size;
        str->size = prev_size + size;

        str->data = (char **)realloc(str->data, sizeof(char **) * str->size);
        for (int i = prev_size; i < str->size; i++)
        {
            str->data[i] = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
        }

        int i = 0;
        int index = 0;
        int str_index = prev_size - 1;
        for (i = balance; i < 8; i++)
        {
            if (str_index >= str->size || index == current_length)
            {
                break;
            }
            str->data[str_index][i] = data[index];
            if (i == 7)
            {
                str_index++;
                i = -1;
            }
            index++;
        }
        while (str_index < str->size)
        {
            if (i > 7)
            {
                i = 0;
                str_index++;
            }
            else
            {
                for (int k = i; k < 8; k++)
                {
                    str->data[str_index][k] = '\0';
                }
            }
            str_index++;
        }
    }
    return;
}

char *get_string(string str)
{
    if (str.size == -1)
    {
        return NULL;
    }
    char *data = (char *)malloc(sizeof(char) * str.size * 8);
    int ic = 0;
    for (int i = 0; i < str.size; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            data[ic] = str.data[i][j];
            if (str.data[i][j] == '\0')
            {
                i = str.size;
                break;
            }
            ic++;
        }
    }
    return data;
}

char *get_string_at_index(string str, int index)
{
    if (str.size <= -1)
    {
        return NULL;
    }
    if (index < 0 || index >= str.size)
    {
        return NULL;
    }
    return str.data[index];
}

int string_length(string str)
{
    if (str.size <= -1)
    {
        return -1;
    }
    int length = 0;
    for (int i = 0; i < 8; i++)
    {
        if (str.data[str.size - 1][i] == '\0')
        {
            break;
        }
        length++;
    }
    length += (8 * (str.size - 1));
    return length;
}

void print_string(string str)
{
    if (str.size <= -1)
    {
        return;
    }
    for (int i = 0; i < str.size; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%c", str.data[i][j]);
            if (str.data[i][j] == '\0')
            {
                i = str.size;
                break;
            }
        }
    }
    return;
}