#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include "colors.h"
#include "strings.h"
#include "des_64.h"
#include "general_methods.h"
#include "priority_queue.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf(RED "[ x ] Please enter correct option\n" RESET);
        return 0;
    }
    int port = 0;
    if (strncmp(argv[1], "-p", 2) == 0)
    {
        printf(YELLOW "[ + ] Setting Port Number...\n" RESET);
        port = atoi(argv[2]);
        printf(GREEN "[ + ] Port Number Set\n" RESET);
    }
    printf(BLUE "[ + ] All set to go\n" RESET);

    int sockfd, connect_int;
    struct sockaddr_in server_address;

    int new_socket;
    struct sockaddr_in new_addr;

    socklen_t addr_size;

    char *buffer = (char*) malloc(sizeof(char) * 1024);
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf(RED "[ x ] CONNECTION NOT ESTABLISHED: Please try after some time\n" RESET);
        return 0;
    }

    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect_int = bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connect_int < 0)
    {
        printf(RED "[ x ] Cannot connect to server\n" RESET);
        return 0;
    }

    if (listen(sockfd, 10) == 0)
    {
        printf(GREEN "[ + ] Listening...\n" RESET);
    }
    else
    {
        printf(RED "[ x ] Not able to listen to any connections\n" RESET);
        return 0;
    }

    priority_queue queue;
    init_heap(&queue);

    while (1)
    {
        new_socket = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
        if (new_socket < 0)
        {
            exit(1);
        }
        printf("Accepted from: %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));
        if ((childpid = fork()) == 0)
        {
            close(sockfd);
            while (1)
            {
                memset(buffer, '\0', sizeof(buffer));
                recv(new_socket, buffer, 1024, 0);
                // decrypt text
                string cipher_text;
                init_string(&cipher_text);
                set_string(&cipher_text, buffer);

                priority_node priority_n;
                priority_n.data = cipher_text;
                priority_n.priority = 0;
                enqueue_pq(&queue, priority_n);
                
                string plain_text;
                init_string(&plain_text);
                set_string(&plain_text, "");
                
                cipher_text = denqueue_pq(&queue)->data;

                int i = 0;
                while (i < cipher_text.size)
                {
                    char *text = get_string_at_index(cipher_text, i);
                    if (text == NULL)
                    {
                        break;
                    }
                    uint8_t *key = convert_string_to_array("$#@pass*");

                    uint8_t *cipher_text_g = convert_string_to_array(text);
                    uint8_t *dcipher_text = decrypt(cipher_text_g, key);

                    char *dcipher = convert_array_to_string(dcipher_text);
                    append_string(&plain_text, dcipher);
                    i++;
                }

                memset(buffer, '\0', sizeof(buffer));
                buffer = get_string(plain_text);

                if (strcmp(buffer, ":exit") == 0)
                {
                    printf("Disconnected\n");
                    memset(buffer, '\0', sizeof(buffer));
                }
                else
                {
                    
                    printf("%s\n", buffer);
                    send(new_socket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }

    return 0;
}