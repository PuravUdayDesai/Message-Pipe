#include <stdio.h>
#include <stdint.h>

uint8_t *function_f(uint8_t *right_partition, uint8_t *key);
uint8_t *encrypt(uint8_t *plain_text, uint8_t *key);
uint8_t *decrypt(uint8_t *cipher_text, uint8_t *key);
uint8_t *initial_permutation(uint8_t *value);
uint8_t *inverse_initial_permutation(uint8_t *value);
uint8_t *permute_pbox(uint8_t *value);
uint8_t *compress_sbox(uint8_t *value, int index);
uint8_t *concatenate_sbox(uint8_t **values);
uint8_t *generate_left_partition(uint8_t *initial_permutation_text);
uint8_t *generate_right_partition(uint8_t *initial_permutation_text);
uint8_t *expand_partition_32_48(uint8_t *partition);

extern uint8_t INITIAL_PERMUTATION[64];
extern uint8_t PARTITION_EXPAND_32_TO_48[48];
extern uint8_t SBOX[8][4][16];
extern uint8_t P_BOX[32];
extern uint8_t INVERSE_INITIAL_PERMUTATION[64];