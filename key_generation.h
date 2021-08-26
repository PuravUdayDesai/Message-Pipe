#include <stdint.h>

uint8_t *compress_key_64_56(uint8_t *key);
uint8_t **generate_c_keys(uint8_t *key);
uint8_t **generate_d_keys(uint8_t *key);
uint8_t **concatenate_key(uint8_t **c_key, uint8_t **d_key);
uint8_t *compress_key_56_48(uint8_t *key);
uint8_t **generate_final_key(uint8_t **concatenated_key);
uint8_t **generate_key(uint8_t *key);

extern uint8_t KEY_COMPRESS_64_TO_56[56];

extern uint8_t NUMBER_OF_SHIFTS[16];

extern uint8_t KEY_COMPRESS_56_TO_48[48];