/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <bits/stdc++.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<poll.h>

using namespace std;

#define DATA_BUFFER 500
#define number_of_connection 10

#define ull unsigned long long int


struct data{

    long long int buffe[1];

};

struct data d1;
 
ull factorial(int n)
{
 
   
    ull ans = 1; 
 
   
    for (ull i = 2; i <= n; i++)
        ans *= i;
 
    return ans;
}


int create_tcp_server_socket(){
    struct sockaddr_in saddr;
   
    int fd,ret_val;
   
    fd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(fd==-1){
        fprintf(stderr,"socket failed[%s]\n",strerror(errno));
        return -1;

    }
    printf("created a sockete with fd: %d\n",fd);

  
    saddr.sin_family=AF_INET;
    saddr.sin_port=8080;
    saddr.sin_addr.s_addr=INADDR_ANY;


    ret_val=bind(fd,(struct sockaddr *)&saddr,sizeof(struct sockaddr_in));

    if(ret_val!=0){
        fprintf(stderr,"bind failed [%s]\n",strerror(errno));
        close(fd);
        return -1;

    }

    ret_val=listen(fd,5);
    if(ret_val!=0){
        fprintf(stderr,"listen failed [%s]\n",strerror(errno));
        close(fd);
        return -1;

    }
    return fd;

}

int main(){
    struct sockaddr_in new_addr;
    int server_fd,ret_val,i;
    socklen_t addrlen;
    char buf[DATA_BUFFER];
    int all_connections[number_of_connection];
    struct pollfd *pfds;
    int nfds=number_of_connection-1,num_open_fds=nfds;
    struct pollfd pollfds[number_of_connection+1];


    server_fd=create_tcp_server_socket();
    if(server_fd==-1){
        fprintf(stderr,"failed to create a server\n");
        return -1;

    }
    pollfds[0].fd=server_fd;
    pollfds[0].events=POLLIN;
    int useclient=0;
    for(int i=1;i<number_of_connection;i++){
        pollfds[i].fd=0;
        pollfds[i].events=POLLIN;
    }
    while(1){
      
        ret_val=poll(pollfds,useclient+1,5000);

        
        if(ret_val>=0){
        
            if(pollfds[0].revents & POLLIN){
  
                printf("returned fd is %d(server 's fd)\n",server_fd);
                int new_fd=accept(server_fd,(struct sockaddr*)&new_addr,&addrlen);
                if(new_fd>=0){
                    printf("accepted a new connection with fd:,%d\n",new_fd);
                    for(int i=1;i<number_of_connection;i++){
                        if(pollfds[i].fd==0){
                            pollfds[i].fd=new_fd;
                            pollfds[i].events=POLLIN;
                            useclient++;
                            break;
                        }
                    }
                }else{
                    fprintf(stderr,"accepted failed [%s]\n",strerror(errno));

                }
                ret_val--;
                if(!ret_val)continue;

            }

      
            for(int i=1 ;i<number_of_connection;i++){
                if(pollfds[i].fd>0 && pollfds[i].revents & POLLIN){

                    memset(buf,0,sizeof(buf));
                   
                    int bufsize=read(pollfds[i].fd,buf,DATA_BUFFER-1);
                    if(bufsize==-1){
                        pollfds[i].fd=0;
                        pollfds[i].events=0;
                        pollfds[i].revents=0;
                        useclient--;

                    }else if(bufsize==0){
                        pollfds[i].fd=0;
                        pollfds[i].events=0;
                        pollfds[i].revents=0;
                        useclient--;
                    }else{
                        printf("from client we received :%d\n",buf[0]-'0');
                        d1.buffe[0]=factorial(buf[0]-'0');
                      

                         
                                
                                char arr[12], *p = arr + 11;
                                                *p = 0;
                                                *p=d1.buffe[0];
                                            
                                    string str=to_string(d1.buffe[0]);
                                    char *cstr = new char[str.length() + 1];
                                    strcpy(cstr, str.c_str());
                                  
                                    FILE* filep;
                                filep=fopen("dataget.txt","a+");
                                    fputs("Data sent is  : ",filep);
                                    fputs(cstr,filep);
                            
                                    fputs("\n",filep);
                                    fclose(filep);

       
                        bufsize = write(pollfds[i].fd,&d1,sizeof(d1));

                    }
                }
            }
        }else{
            printf("failed to connect.\n");
        }
    }
}