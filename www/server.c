#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 256

void commun(int);
void DieWithError(char*);

int main(int argc,char **argv){
	int cliSock;
	//���ۂ̒ʐM�p�\�P�b�g
	int servSock=socket(PF_INET,SOCK_STREAM,0);
	//�҂��󂯐�p�\�P�b�g
	struct sockaddr_in servAddress;
	struct sockaddr_in clientAddress;
	unsigned int szClientAddr;
	
	servAddress.sin_family=AF_INET;
	servAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddress.sin_port=htons(80);
	bind(servSock,(struct sockaddr *)&servAddress,sizeof(servAddress));
	listen(servSock,5);  //���ԑ҂����Ă������N���C�A���g��[��ڂ̈���](���ۂ�OS�ɂ���ċ������قȂ�)
	//������ƌ�����5�l�����ڑ��ł���킯�ł͂Ȃ�
	while(1){
		szClientAddr=sizeof(clientAddress);
		cliSock=accept(servSock,(struct sockaddr *)&clientAddress,&szClientAddr);
		commun(cliSock);
		close(cliSock);
	}
	
	close(servSock);
	
	return 0;
}

void commun(int sock){
	char buf[BUF_SIZE];
	int len_r=recv(sock,buf,BUF_SIZE,0);
	char *message="���o�[�E�H�[�N�k��B";
	if(len_r<=0)DieWithError("recv()failed");
	buf[len_r]='\0';
	printf("%s\n",buf);
	if(send(sock,message,strlen(message),0)!=strlen(message))DieWithError("send() sent a massage of unexpected bytes");
}

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}







