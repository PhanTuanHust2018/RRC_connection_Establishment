#include <stdio.h>
#include <pthread.h>    //for thread
#include <sys/socket.h> // for socket(), connect(), send(), and recv()
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h> //for sockaddr_in and inet_addr()
#include <string.h>
#include <unistd.h> //for close

#include "param.h"

void *UE_client_socket(void *UE)
{
    int sockfd = -1;
    struct sockaddr_in server_addr;
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(10000);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect fail\n");
    }
    else
    {
        memcpy(buffer, UE, sizeof(UE));
        if (send(sockfd, (void *)(&buffer), sizeof(buffer), 0) < 0)
        {
            perror("send RRC setup request fail\n");
        }
    }
}

int main()
{
    printf("Hello UE\n");

    for (int i = 0; i < NUMBER_UE; i++)
    {
        pthread_t t_UE;
        UE *UE_ = (UE *)malloc(sizeof(UE));
        UE_->UE_ID = i;
        UE_->state = RRC_CONNNECTED;
        pthread_create(&t_UE, NULL, UE_client_socket, (void *)UE_);
    }
    pthread_exit(NULL);
    return 0;
}