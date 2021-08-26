#include <stdlib.h>
#include "des_64.h"
uint8_t *initial_permutation(uint8_t *value)
{
    uint8_t *permuted_text = (uint8_t *)calloc(64, sizeof(uint8_t));
    for (int i = 0; i < 64; i++)
    {
        permuted_text[i] = value[INITIAL_PERMUTATION[i] - 1];
    }

    return permuted_text;
}