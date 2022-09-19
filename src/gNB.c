#include <stdio.h>
#include <pthread.h>    //for thread
#include <sys/socket.h> // for socket(), connect(), send(), and recv()
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h> //for sockaddr_in and inet_addr()
#include <string.h>
#include <unistd.h> //for close

#include "param.h"

void *gNB_server_socket()
{
    int listenfd = -1, connfd = -1;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(10000);
    bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listenfd, NUMBER_UE);

    while (1)
    {
        socklen_t addr_size;
        addr_size = sizeof(struct sockaddr_in);
        connfd = accept(listenfd, (struct sockaddr *)&client_addr, &addr_size);
        if (recv(connfd, (void *)(&buffer), sizeof(buffer), 0) < 0)
        {
            perror("recive request fail\n");
        }
        else
        {
            printf("UE_ID =  %d\n", *(int *)buffer);
            printf("STATE =  %d\n\n", *((int *)(buffer) + 1));
        }
        close(connfd);
    }
    close(listenfd);
}
int main()
{
    printf("Hello gNB\n");
    pthread_t t_gNB;
    pthread_create(&t_gNB, NULL, gNB_server_socket, NULL);
    pthread_join(t_gNB, NULL);
    return 0;
}