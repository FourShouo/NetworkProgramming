#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);
int prepare_server_socket(int);
void commun(int);

int main(int argc, char *argv[])
{
    if (argc != 3)
        DieWithError("usage: .client ip_address port");

    //まだ書いてね
    return 0;
}

void DieWithError(char *erroMessage)
{
    perror(erroMessage);
    exit(1);
}

int prepare_client_socktet(char *ipaddr, int port)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        DieWithError("socket() failed");

    struct socketaddr_in target;
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = htonl(//まだ書いてね);
    target.sin_port = htonl(port);

    bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));

    return servSock;
}

//全然書くの途中ですよ