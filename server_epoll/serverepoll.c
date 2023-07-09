

//serverepoll.cpp will be run in parallel with clientudp.cpp

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<poll.h>
#include<sys/epoll.h>


#define DATA_BUFFER 20
#define MAX_CONNECTIONS 10
 #define ull unsigned long long int


 struct data{

    long long int buffe[1];
};

struct data d1;

ull factorial(int N)
{
 
    ull f = 1; 
 
  
    for (ull i = 2; i <= N; i++)
        f *= i;
 
    return f;
}


int create_tcp_server_socket(){
    struct sockaddr_in saddr;

    int fd,ret_val;


    fd=socket(AF_INET,SOCK_DGRAM,0);
    if(fd==-1){
        fprintf(stderr,"socket failed [%s]\n",strerror(errno));

        return -1;
    }
    printf("created a socket with fd: %d\n",fd);


   
    saddr.sin_family=AF_INET;
    saddr.sin_port=8080;
    saddr.sin_addr.s_addr=INADDR_ANY;

    
    ret_val=bind(fd,(struct sockaddr *)&saddr,sizeof(struct sockaddr_in));

    if(ret_val!=0){
        fprintf(stderr,"bind failed [%s]\n",strerror(errno));
        close(fd);
        return -1;
    }

    return fd;
}

int main(){

    struct sockaddr_in new_addr;
    int server_fd,ret_val,i,efd,s;

    socklen_t addrlen;
    char buf[DATA_BUFFER];
    struct pollfd *pfds;
    int nfds=MAX_CONNECTIONS-1,num_open_fds=nfds;
    struct epoll_event pollfd;
    struct epoll_event *pollfds;

  
    server_fd=create_tcp_server_socket();

    if(server_fd==-1){
        fprintf(stderr,"failed to create a server\n");
        return -1;
    }

    efd=epoll_create1(0);
    pollfd.data.fd=server_fd;
    pollfd.events=EPOLLIN;
    s=epoll_ctl(efd,EPOLL_CTL_ADD,server_fd,&pollfd);
    if(s==-1){
        perror("error epoll_ctl");
        abort();

    }
    int useclient=0;

   
    pollfds=(struct epoll_event *)calloc(MAX_CONNECTIONS,sizeof(pollfd));


    for(int i=0;i<MAX_CONNECTIONS;i++){
        pollfds[i].data.fd=0;
        pollfds[i].events=EPOLLIN;
    }

    while(1){
       
        ret_val=epoll_wait(efd,pollfds,MAX_CONNECTIONS,-1);
        if(ret_val==0){
            break;
        }
        for(int j=0;j<ret_val;j++){
            int fd=pollfds[i].data.fd;
            printf("returned fd is %d (server 's fd\n",server_fd);
            memset(buf,0,sizeof(buf));


     
            int bufsize=recv(fd,buf,sizeof(buf),0);


            if(bufsize==-1){
                pollfds[i].data.fd=0;
                pollfds[i].events=0;
                useclient--;
                printf("error reading");

            }else if(bufsize==0){
                pollfds[i].data.fd=0;
                pollfds[i].events=0;
                useclient--;
                break;
            }else{
                printf("From client: %d\n",buf[0]-'0');
              

            }
              long long int a=factorial(buf[0]-'0');
             d1.buffe[0]=a;
         
               bufsize=write(fd,&d1,sizeof(d1));
               printf("send againtto the client %lld\n",d1.buffe[0]);
        }
    }
    for(int i=0;i<MAX_CONNECTIONS;i++){
        close(pollfds[i].data.fd);

    }
    free(pollfds);
    close(server_fd);
    return 0;
}