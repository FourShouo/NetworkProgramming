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
void my_scanf(char *, int);
void commun(int);
void read_until_delim(int, char *, char, int);

int main(int argc, char *argv[])
{
    if (argc != 3)
        DieWithError("usage: ./client ip_address port");

    //まだ書いてね
    int sock = prepare_client_socktet(argv[1], atoi(argv[2]));
    commun(sock);
    close(sock);
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
    target.sin_addr.s_addr = inet_addr(ipaddr); //まだ書いてね);
    target.sin_port = htonl(port);
    if (connect(sock, (struct sockaddr *)&target, sizeof(target)) < 0)
    {
        DieWithError("connect() failed");
    }

    return sock;
}

void my_scanf(char *buf, int num_letter)
{
    char format[20];
    sprintf(format, "%s%d%s", "%", num_letter, "s%*[^\n]");
    scanf(format, buf);
    getchar();
}

void commun(int sock)
{
    char cmd[2] = "";
    char withdraw[MONEY_DIGIT_SIZE + 1];
    char deposit[MONEY_DIGIT_SIZE + 1];
    char msg[BUF_SIZE];

    printf("0:引き出し　1:預け入れ　2:残高照会\n");
    printf("何をしますか？　＞　");

    my_scanf(cmd, 1);

    swich(cmd[0])
    {
    case '0':
        //引き出し処理
        printf("引き出す金額を入力してください　＞　");
        my_scanf(withdraw, MONEY_DIGIT_SIZE);

        sprintf(msg, "%s_0_", withdraw);
        break;
    case '1':
        //預け入れ処理
        printf("預け入れる金額を入力してください　＞　");
        my_scanf(deposit, MONEY_DIGIT_SIZE);

        sprintf(msg, "%s_0_", deposit);
        break;
    case '2':
        //残高照会
        strcpy(msg, "0_0_");
        break;
    default:
        //unknownエラー
        printf("番号が確認できませんでした。\n");
        return;
    }
    if (send(sock, msg, strlen(msg), 0) != strlen(msg))
        DieWithError("send() sent a message of unexpected bytes");

    read_until_delim(sock, msg, '_', BUF_SIZE);
    printf("残高は%d円になりました", atoi(msg));
}

void read_until_delim(int sock, char *buf, char delimiter, int max_length)
{
    int len_r = 0;
    int index_letter = 0;

    while (index_letter < max_length - 1)
    {
        if ((len_r = recv(sock, buf + index_letter, 1, 0)) <= 0)
        {
            DieWithErroe("recv() failed");
            return;
        }

        if (buf[index_letter] == delimiter)
            break;
        else
            index_letter++;
    }
    //一文字受信

    buf[index_letter] = '\0';
}

//全然書くの途中ですよ--終了