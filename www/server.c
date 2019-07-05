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
	//実際の通信用ソケット
	int servSock=socket(PF_INET,SOCK_STREAM,0);
	//待ち受け専用ソケット
	struct sockaddr_in servAddress;
	struct sockaddr_in clientAddress;
	unsigned int szClientAddr;
	
	servAddress.sin_family=AF_INET;
	servAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddress.sin_port=htons(80);
	bind(servSock,(struct sockaddr *)&servAddress,sizeof(servAddress));
	listen(servSock,5);  //順番待ちしてもいいクライアント数[二つ目の引数](実際はOSによって挙動が異なる)
	//だからと言って5人同時接続できるわけではない
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
	char buf_old[BUF_SIZE];
	char buf2[BUF_SIZE*2];
	char kuuhaku[]="\r\n\r\n";
	int len_r;
	
	buf_old[0]='\0';
	
	char *message="HTTP /1.1 200 OK \r\nContent-Type:text/html; charset=shift-jis\r\n\r\n<IDOVCTYPE html><html><head><title>ネットワークプログラミングのwebサイト</title></head><body>ネットワークダイスキ</body></html>";
	
	while(len_r=recv(sock,buf,BUF_SIZE,0)>0){
		buf[len_r]="\0";
		sprintf(buf2,"%s%s",buf_old,buf);
		if(strstr(buf2,kuuhaku))break;
		sprintf(buf_old,"%s",buf);
	}
		
	if(len_r<=0)DieWithError("recv()failed");
	printf("received HTTP Request.\n");
	buf[len_r]='\0';
	printf("%s\n",buf);
	if(send(sock,message,strlen(message),0)!=strlen(message))DieWithError("send() sent a massage of unexpected bytes");
}

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}
