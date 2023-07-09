#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int main(){

    struct sockaddr_in saddr;

    int fd, ret_val,new_ret_val;

    fd=socket(AF_INET,SOCK_DGRAM,0);
    if(fd==-1){
        fprintf(stderr,"socket failed\n");
        return -1;

    }

    printf("created a socket with fd: %d\n",fd);
    
    saddr.sin_family=AF_INET;
    saddr.sin_port=8080;
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");



   
    ret_val=connect(fd,(struct sockaddr *)&saddr,sizeof(struct sockaddr_in));

    if(ret_val==-1){
        fprintf(stderr,"connect failed\n");
        close(fd);
        return -1;

    }
    printf("connected\n");

    char data_buf[20];
    char ans[20];
    int i=1;
    while(i<=20){
    data_buf[0]=i+'0';
    

        ret_val=send(fd,data_buf,sizeof(data_buf),0);
        printf("send message (len %d bytes): %d\n",ret_val,data_buf[0]-'0');


        i++;
    }

    close(fd);
    return 0;
}