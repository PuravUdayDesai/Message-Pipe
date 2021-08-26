#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdint.h>
#include "strings.h"

typedef struct ip_v4
{
    uint8_t first_block;
    uint8_t second_block;
    uint8_t third_block;
    uint8_t fourth_block;
} ip_v4;

typedef struct mac
{
    uint8_t first_octal;
    uint8_t second_octal;
    uint8_t third_octal;
    uint8_t fourth_octal;
    uint8_t fifth_octal;
    uint8_t sixth_octal;
} mac;

typedef struct user
{
    string user_name;
    mac mac_address;
    ip_v4 ip_address;
} user;

#endif