#include <stdio.h>  
#include <linux/input.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#define DEV_PATH "/dev/input/event2"   //difference is possible  
#define Server_IP "192.168.43.159"
#define Server_Prot 19537
pthread_t thread[2];
int Over=0,Go=0,Back=0;
void *thread1()
{/*{{{*/
	int se_socket;
	struct sockaddr_in se_addr;
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(Server_Prot);
	se_addr.sin_addr.s_addr=inet_addr(Server_IP);
	se_socket=socket(AF_INET,SOCK_STREAM,0);	
	int con=connect(se_socket,(void*)&se_addr,sizeof(struct sockaddr_in));
	if(con!=0)
			{/*{{{*/
				printf("Connect TCP server fail\n");
				return (void *)-1;
			}else{
					printf("Connect TCP server successful\n");
			}/*}}}*/
	char *str=(char *)malloc(10);
	char *str1="1";
	char *str2="2";
	while(1){
			if(Go==1)
			{
				write(se_socket,str1,sizeof(2));
				printf("Go=%d\n",Go);
			}else if(Back==1)
			{
				write(se_socket,str2,sizeof(2));
				printf("Back=%d\n",Back);
			}else{
				write(se_socket,"5",sizeof(2));
			}
			printf("Input Key\n");
			usleep(500000);
	}
	close(se_socket);
	return 0;
}/*}}}*/
void *thread2()  
{  /*{{{*/
    int keys_fd;  
    char ret[2];  
    struct input_event t;  
    keys_fd=open(DEV_PATH, O_RDONLY);  
    if(keys_fd <= 0)  
    {  /*{{{*/
        printf("open /dev/input/event2 device error!\n");  
        return (void *)-1;  
	}else{
		printf("Please Input Key\n");
    }  /*}}}*/
    while(1)  
    {  
        if(read(keys_fd, &t, sizeof(t)) == sizeof(t))  
        {  
            if(t.type==EV_KEY)  
                if(t.value==0 || t.value==1)  
                {  
 //                   printf("key  %d %s\n",t.code, (t.value) ? "Pressed" : "Released");  
					if(t.code==17)
					{
						Go=t.value;
					}
					if(t.code==31)
					{
						Back=t.value;
					}
                    if(t.code == KEY_ESC)
					{
						Over=1;	
						break;
					}	
                }  
        }  
    }  
    close(keys_fd);  
    return 0;  
} /*}}}*/
int main()
{
	pthread_create(&thread[0],NULL,thread1,NULL);	
	sleep(1);
	pthread_create(&thread[1],NULL,thread2,NULL);
	while(!Over);
	return 0;

}

