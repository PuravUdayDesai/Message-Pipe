#include <stdlib.h>
#include "des_64.h"
uint8_t *permute_pbox(uint8_t *value)
{
    uint8_t *permuted_text = (uint8_t *)calloc(32, sizeof(uint8_t));
    for (int i = 0; i < 32; i++)
    {
        permuted_text[i] = value[P_BOX[i] - 1];
    }

    return permuted_text;
}