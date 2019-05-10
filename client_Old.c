#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>  //close—p
#include<string.h>

//#include<stdio.h>

void commun(int);

int main(int argc,char **argv){
	
	int sock=socket(PF_INET,SOCK_STREAM,0);
	
//	printf("sock is %d\n",sock);
	
	struct sockaddr_in target;
	
	target.sin_family=AF_INET;
	target.sin_addr.s_addr=inet_addr("10.13.64.20");
	target.sin_port=htons(10001);
	
	connect(sock,(struct sockaddr *)&target,sizeof(target));
	
	commun(sock);
	
	close(sock);
	
	return 0;
}

void commun(int sock){
	char *message="Ä‚«’¹H‚×‚½‚¢!";
	send(sock,message,strlen(message),0);
}


