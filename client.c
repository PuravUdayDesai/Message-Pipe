#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "colors.h"
#include "strings.h"
#include "des_64.h"
#include "general_methods.h"

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        printf(RED "[ x ] Please enter correct option\n" RESET);
        return 0;
    }

    printf("________ ________________ __________\n");
    printf("___  __ \\____  _/___  __ \\___  ____/\n");
    printf("__  /_/ / __  /  __  /_/ /__  __/\n");   
    printf("_  ____/ __/ /   _  ____/ _  /___\n");   
    printf("/_/      /___/   /_/      /_____/\n");

    int port = 0;
    string username;
    init_string(&username);
    if (strncmp(argv[1], "-p", 2) == 0)
    {
        printf(YELLOW "[ + ] Setting Port Number...\n" RESET);
        port = atoi(argv[2]);
        printf(GREEN "[ + ] Port Number Set\n" RESET);
    }
    else if (strncmp(argv[1], "-u", 2) == 0)
    {
        printf(YELLOW "[ + ] Setting Username...\n" RESET);
        set_string(&username, argv[2]);
        printf(GREEN "[ + ] Username Set\n" RESET);
    }
    if (strncmp(argv[3], "-u", 2) == 0)
    {
        printf(YELLOW "[ + ] Setting Username...\n" RESET);
        set_string(&username, argv[4]);
        printf(GREEN "[ + ] Username Set\n" RESET);
    }
    else if (strncmp(argv[3], "-p", 2) == 0)
    {
        printf(YELLOW "[ + ] Setting Port Number...\n" RESET);
        port = atoi(argv[4]);
        printf(GREEN "[ + ] Port Number Set\n" RESET);
    }
    printf(BLUE "[ + ] All set to go\n" RESET);

    int client_socket, connect_int;
    struct sockaddr_in server_addr;
    char *buffer = NULL;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        printf(RED "[ x ] CONNECTION NOT ESTABLISHED: Please try after some time\n" RESET);
        return 0;
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect_int = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_int < 0)
    {
        printf(RED "[ x ] Cannot connect to server\n" RESET);
        return 0;
    }

    int command_flag = 0;
    while (1)
    {
        command_flag = 0;
        printf(BLACK "$ " RESET);
        char ch = '\0';
        string message;
        init_string(&message);
        set_string(&message, get_string(username));
        append_string(&message, " : ");

        string command;
        init_string(&command);
        set_string(&command, "");

        while (1)
        {
            scanf("%c", &ch);
            if (ch == '\n')
            {
                break;
            }
            else if (ch == ':')
            {
                command_flag = 1;
            }
            char *ch_ptr = (char *)malloc(sizeof(char) * 2);
            ch_ptr[0] = ch;
            ch_ptr[1] = '\0';
            if (command_flag == 1)
            {
                append_string(&command, ch_ptr);
            }
            else
            {
                append_string(&message, ch_ptr);
            }
        }

        if (command_flag == 1)
        {
            buffer = get_string(command);
        }
        else
        {
            buffer = get_string(message);
        }

        // encrypt string
        int i = 0;
        string main_message;
        init_string(&main_message);
        set_string(&main_message, buffer);

        string cipher_message;
        init_string(&cipher_message);
        set_string(&cipher_message, "");

        while (i < main_message.size)
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
            append_string(&cipher_message, cipher);

            i++;
        }

        memset(buffer, '\0', sizeof(buffer));
        buffer = get_string(cipher_message);

        send(client_socket, buffer, strlen(buffer), 0);

        if (command_flag == 1)
        {
            buffer = get_string(command);
        }
        if (strcmp(buffer, ":exit") == 0)
        {
            close(client_socket);
            printf(WHITE "[ + ] Closing all connections\n" RESET);
            printf(CYAN "[ + ] Thank you\n" RESET);
            return 0;
        }
        if (recv(client_socket, buffer, 1024, 0) > 0)
        {
            printf(CYAN "Server: %s\n" RESET, buffer);
        }
    }
    return 0;
}