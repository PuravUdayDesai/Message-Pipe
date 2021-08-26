#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "key_generation.h"
#include "general_methods.h"

uint8_t KEY_COMPRESS_64_TO_56[56] =
    {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4};

uint8_t NUMBER_OF_SHIFTS[16] =
    {
        1,
        1,
        2,
        2,
        2,
        2,
        2,
        2,
        1,
        2,
        2,
        2,
        2,
        2,
        2,
        1};

uint8_t KEY_COMPRESS_56_TO_48[48] =
    {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32};

uint8_t *compress_key_64_56(uint8_t *key)
{
    if (key == NULL)
    {
        return NULL;
    }
    uint8_t *compressed_key = (uint8_t *)malloc(sizeof(uint8_t) * 56);
    for (int i = 0; i < 56; i++)
    {
        compressed_key[i] = key[KEY_COMPRESS_64_TO_56[i] - 1];
    }
    return compressed_key;
}

uint8_t **generate_c_keys(uint8_t *key)
{
    uint8_t **c_keys = (uint8_t **)malloc(sizeof(uint8_t *) * 17);
    for (int i = 0; i < 17; i++)
    {
        c_keys[i] = (uint8_t *)malloc(sizeof(uint8_t) * 28);
    }
    for (int j = 0; j < 28; j++)
    {
        c_keys[0][j] = key[j];
    }
    for (int i = 1; i < 17; i++)
    {
        c_keys[i] = shift_left(c_keys[i - 1], 28, NUMBER_OF_SHIFTS[i - 1]);
    }

    return c_keys;
}

uint8_t **generate_d_keys(uint8_t *key)
{
    uint8_t **d_keys = (uint8_t **)malloc(sizeof(uint8_t *) * 17);
    for (int i = 0; i < 17; i++)
    {
        d_keys[i] = (uint8_t *)malloc(sizeof(uint8_t) * 28);
    }
    for (int j = 0; j < 28; j++)
    {
        d_keys[0][j] = key[j + 28];
    }
    for (int i = 1; i < 17; i++)
    {
        d_keys[i] = shift_left(d_keys[i - 1], 28, NUMBER_OF_SHIFTS[i - 1]);
    }

    return d_keys;
}

uint8_t **concatenate_key(uint8_t **c_key, uint8_t **d_key)
{
    if (*c_key == NULL || *d_key == NULL)
    {
        return NULL;
    }
    uint8_t **concatenate_key = (uint8_t **)malloc(sizeof(uint8_t *) * 16);
    for (int i = 0; i < 16; i++)
    {
        concatenate_key[i] = (uint8_t *)malloc(sizeof(uint8_t) * 56);
    }

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            concatenate_key[i][j] = c_key[i + 1][j];
            concatenate_key[i][j + 28] = d_key[i + 1][j];
        }
    }

    return concatenate_key;
}
uint8_t *compress_key_56_48(uint8_t *key)
{
    uint8_t *compressed_key = (uint8_t *)malloc(sizeof(uint8_t) * 48);
    for (int i = 0; i < 48; i++)
    {
        compressed_key[i] = key[KEY_COMPRESS_56_TO_48[i] - 1];
    }
    return compressed_key;
}

uint8_t **generate_final_key(uint8_t **concatenated_key)
{
    uint8_t **final_key = (uint8_t **)malloc(sizeof(uint8_t *) * 16);
    for (int i = 0; i < 16; i++)
    {
        final_key[i] = compress_key_56_48(concatenated_key[i]);
    }
    return final_key;
}
uint8_t **generate_key(uint8_t *key)
{
    uint8_t *compressed_key = compress_key_64_56(key);
    uint8_t **c_keys = generate_c_keys(compressed_key);
    uint8_t **d_keys = generate_d_keys(compressed_key);
    uint8_t **concat_keys = concatenate_key(c_keys, d_keys);
    uint8_t **final_keys = generate_final_key(concat_keys);
    return final_keys;
}