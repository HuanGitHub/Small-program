#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#define Loca_IP "127.0.0.1"
#define Loca_Prot 8080
int main()
{
	int Over=0;
	int se_socket,cl_socket;
	int len;
	struct sockaddr_in se_addr,cl_addr;	
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(Loca_Prot);
	se_addr.sin_addr.s_addr=inet_addr(Loca_IP);
	se_socket=socket(AF_INET,SOCK_STREAM,0);
	if(se_socket<0)
	{/*{{{*/
		printf("socket fail");
		exit(0);
	}/*}}}*/
	if(bind(se_socket,(void*)&se_addr,sizeof(se_addr))==-1)
	{/*{{{*/
		printf("bind fail");
		exit(0);
	}/*}}}*/
	listen(se_socket,5);
	int i;
	char buf[100];
	struct tm *timeinfo;
	char *str=(char *)malloc(10);
	cl_socket=accept(se_socket,(void*)&cl_addr,&len);
	while(1)
	{/*{{{*/
			read(cl_socket,buf,sizeof(buf));
			for(i=0;i<10;i++)
		   		printf("%d\n",buf[i]);
			memset(buf,0,sizeof(buf));
	}/*}}}*/
	close(cl_socket);
	close(se_socket);

}


























