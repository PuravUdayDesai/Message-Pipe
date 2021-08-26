#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "general_methods.h"

uint8_t *xor_array(uint8_t *array_one, uint8_t *array_two, int length)
{
    uint8_t *xored_array = NULL;
    xored_array = (uint8_t *)calloc(length, sizeof(uint8_t));
    for (int i = 0; i < length; i++)
    {
        xored_array[i] = (uint8_t)(array_one[i] ^ array_two[i]);
    }
    return xored_array;
}

int convert_binary_decimal(char *binary_number, int length)
{
    int decimal_number = 0;
    for (int i = 0; i < length; i++)
    {
        int binary_character = binary_number[i] - '0';
        decimal_number += binary_character * (int)pow(2, (length - 1) - i);
    }
    return decimal_number;
}

char *convert_decimal_binary(int decimal_number)
{
    char *binary_number = (char *)malloc(sizeof(char) * 4);
    char num = decimal_number;
    for (int i = 3; i >= 0; i--)
    {
        binary_number[i] = (char)('0' + ((num & (1 << (7 - i))) >> (7 - i)));
    }

    return binary_number;
}

uint8_t *shift_left(uint8_t *value, int length, int number_of_shifts)
{
    uint8_t *shifted_value = (uint8_t *)calloc(length, sizeof(uint8_t));
    for (int i = 1; i <= number_of_shifts; i++)
    {
        uint8_t temp = value[0];
        for (int j = 0; j < length; j++)
        {
            shifted_value[j] = value[j + 1];
        }
        shifted_value[length - 1] = temp;
        value = shifted_value;
    }
    return shifted_value;
}

char *convert_decimal_binary_8(int decimal_number)
{
    char *binary_number = (char *)malloc(sizeof(char) * 8);
    char num = decimal_number;
    for (int i = 7; i >= 0; i--)
    {
        binary_number[i] = (char)('0' + ((num & (1 << (7 - i))) >> (7 - i)));
    }

    return binary_number;
}

uint8_t *convert_string_to_array(char *str)
{
    uint8_t *arr = (uint8_t *)malloc(sizeof(uint8_t) * 64);
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        char current_char = str[i];
        int decimal_char = current_char;
        char *binary_form = convert_decimal_binary_8(decimal_char);
        for (int j = 0; j < 8; j++)
        {
            arr[index] = binary_form[j] - '0';
            index++;
        }
    }
    return arr;
}

char *convert_array_to_string(uint8_t *arr)
{
    char *str = (char *)malloc(sizeof(char) * 8);
    char *binary = (char *)malloc(sizeof(char) * 8);
    int bin_index = 0;
    int str_index = 0;
    for (int i = 0; i < 65; i++)
    {
        if (i % 8 == 0 && i != 0)
        {
            int decimal = convert_binary_decimal(binary, 8);
            str[str_index] = (char)decimal;
            str_index++;
            bin_index = 0;
        }
        binary[bin_index] = arr[i] + '0';
        bin_index++;
    }
    return str;
}