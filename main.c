#include <stdio.h>
#include <string.h>
#include "strings.h"
#include "priority_queue.h"
#include "hashtable.h"
#include "des_64.h"
#include "general_methods.h"

int main(int argc, char **argv)
{
    /*
    ip_v4 ip_address;
    ip_address.first_block = 192;
    ip_address.second_block = 168;
    ip_address.third_block = 90;
    ip_address.fourth_block = 128;

    mac mac_address;
    mac_address.first_octal = 0x1C;
    mac_address.second_octal = 0x10;
    mac_address.third_octal = 0x11;
    mac_address.fourth_octal = 0xC2;
    mac_address.fifth_octal = 0xDE;
    mac_address.sixth_octal = 0xFF;

    user user_data;
    user_data.ip_address = ip_address;
    user_data.mac_address = mac_address;
    set_string(&(user_data.user_name), "purav");

    hash_table table;
    put(&table, 0, user_data);

    user *user_get = NULL;
    user_get = get(table, 0);
    printf("IP Address: %d.%d.%d.%d\n", user_get->ip_address.first_block,
                                        user_get->ip_address.second_block,
                                        user_get->ip_address.third_block,
                                        user_get->ip_address.fourth_block
                                        );
    printf("MAC Address: %X:%X:%X:%X:%X:%X\n",  user_get->mac_address.first_octal,
                                                user_get->mac_address.second_octal,
                                                user_get->mac_address.third_octal,
                                                user_get->mac_address.fourth_octal,
                                                user_get->mac_address.fifth_octal,
                                                user_get->mac_address.sixth_octal
                                                );
    printf("Name: %s\n", get_string(user_data.user_name));


    string message;
    set_string(&message, "hello, can I call you now?");
    int i = 0;
    while (i < message.size)
    {
        char *text = get_string_index(message, i);
        if (text == NULL)
        {
            break;
        }
        uint8_t *plain_text = convert_string_to_array(text);

        uint8_t *key = convert_string_to_array("$#@pass*");

        uint8_t *cipher_text = encrypt(plain_text, key);
        char *cipher = convert_array_to_string(cipher_text);
        printf("Cipher Text: %s\n", cipher);

        uint8_t *dcipher_text = decrypt(cipher_text, key);
        char *dcipher = convert_array_to_string(dcipher_text);
        printf("Dcipher Text: %s\n", dcipher);
        i++;
    }
    */

    
    char cipher_buffer[2048];
    memset(cipher_buffer, 0, sizeof(cipher_buffer));
    char buffer[2048] = "HelloHi";
    string message;
    set_string(&message, buffer);
    int i = 0;
    while (i < message.size)
    {
        char *text = get_string_at_index(message, i);
        if (text == NULL)
        {
            break;
        }
        uint8_t *plain_text = convert_string_to_array(text);
        uint8_t *key = convert_string_to_array("$#@pass*");

        uint8_t *cipher_text = encrypt(plain_text, key);
        char *cipher = convert_array_to_string(cipher_text);
        strcpy(cipher_buffer, cipher);
        i++;
    }

    char plain_buffer[2048];
    memset(plain_buffer, 0, sizeof(plain_buffer));
    string message2;
    set_string(&message2, cipher_buffer);
    i = 0;
    while (i < message2.size)
    {
        char *text = get_string_at_index(message2, i);
        if (text == NULL)
        {
            break;
        }
        uint8_t *key = convert_string_to_array("$#@pass*");

        uint8_t *cipher_text_g = convert_string_to_array(text);
        uint8_t *dcipher_text = decrypt(cipher_text_g, key);

        char *dcipher = convert_array_to_string(dcipher_text);
        strcpy(plain_buffer, dcipher);
        printf("Dcipher Text: %s\n", dcipher);
        i++;
    }
    printf("Decrypted Text: %s\n", plain_buffer);
    

   /*
    string str;
    init_string(&str);
    set_string(&str, "Purav Uday Desai");
    print_string(str);
    printf("\n------------------------------------\n");
    printf("Length: %d\n", string_length(str));
    append_string(&str, " Hi Hello How are you?");
    print_string(str);
    printf("\n------------------------------------\n");
    printf("Length: %d\n", string_length(str));
    append_string(&str, " Hi");
    print_string(str);
    printf("\n------------------------------------\n");
    printf("Length: %d\n", string_length(str));
    append_string(&str, " Hi, Hey you know I compleated the majority of my errorneous code today, isn't that amazing?");
    print_string(str);
    printf("\n------------------------------------\n");
    printf("Length: %d\n", string_length(str));
    */
    return 0;
}