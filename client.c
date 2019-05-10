//コンパイル

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>  //close用
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define BUF_SIZE 256

void commun(int);
void DieWithError(char*);

int main(int argc,char **argv){
	
	if(argc!=3)DieWithError("arguments is not available");
	
//	char *server_ipaddr="10.13.64.20";↓更新後
	char *server_ipaddr=argv[1];
//	int server_port=10001;↓更新後
	int server_port=atoi(argv[2]);
	int sock=socket(PF_INET,SOCK_STREAM,0);
	
	if(sock<0)DieWithError("socket()failed");
	
//	printf("sock is %d\n",sock);
	
	struct sockaddr_in target;
	
	target.sin_family=AF_INET;
	target.sin_addr.s_addr=inet_addr(server_ipaddr);
	target.sin_port=htons(server_port);
	
	if(connect(sock,(struct sockaddr *)&target,sizeof(target))<0)DieWithError("connect()failed");
	
	commun(sock);
	
	close(sock);
	
	return 0;
}

void commun(int sock){
	char buf[BUF_SIZE];
	char *message="通称「リバーウォーク」、「リバ」";
	if(send(sock,message,strlen(message),0)!=strlen(message))DieWithError("send()sent a message of unexpected bytes");
	int len_r=recv(sock,buf,BUF_SIZE,0);
	if(len_r<=0)DieWithError("recv()failed");
	buf[len_r]='\0';
	printf("%s\n",buf);
}

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}

