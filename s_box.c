#include <stdlib.h>
#include <string.h>
#include "des_64.h"
#include "general_methods.h"

uint8_t *compress_sbox(uint8_t *value, int index)
{
    uint8_t *compressed_value = (uint8_t *)calloc(4, sizeof(uint8_t));
    char *row_index_binary = (char *)calloc(2, sizeof(char));
    char *column_index_binary = (char *)calloc(4, sizeof(char));
    int row_index_binary_index = 0;
    int column_index_binary_index = 0;
    for (int i = 0; i < 6; i++)
    {
        if (i == 0 || i == 5)
        {
            row_index_binary[row_index_binary_index] = (char)(value[i] + '0');
            row_index_binary_index++;
        }
        else
        {
            column_index_binary[column_index_binary_index] = (char)(value[i] + '0');
            column_index_binary_index++;
        }
    }

    int row_index_decimal = convert_binary_decimal(row_index_binary, 2);
    int column_index_decimal = convert_binary_decimal(column_index_binary, 4);
    uint8_t compressed_decimal_value = SBOX[index][row_index_decimal][column_index_decimal];
    char *compressed_binary_value = convert_decimal_binary(compressed_decimal_value);
    int i = 0;
    while (compressed_binary_value[i] != '\0')
    {
        if (i > 3)
        {
            break;
        }
        compressed_value[i] = compressed_binary_value[i] - '0';
        i++;
    }
    return compressed_value;
}

uint8_t *concatenate_sbox(uint8_t **values)
{
    uint8_t *concatenated_value = (uint8_t *)calloc(32, sizeof(uint8_t));
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            concatenated_value[index] = values[i][j];
            index++;
        }
    }

    return concatenated_value;
}