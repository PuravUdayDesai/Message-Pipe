#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

#define MAX_STRING_SIZE 8

typedef struct string
{
    char **data;
    int size;
} string;

void init_string(string *str);
void set_string(string *str, char *data);
void append_string(string *str, char *data);
char *get_string(string str);
char *get_string_at_index(string str, int index);
int string_length(string str);
void print_string(string str);
void free_string(string *str);

#endif