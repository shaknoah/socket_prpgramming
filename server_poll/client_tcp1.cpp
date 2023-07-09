 #include <stdio.h>
 #include <errno.h>
 #include <netinet/in.h> 
 #include <netdb.h> 
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<pthread.h>

using namespace std;

struct data{

    long long int buffe[1];
  
};

struct data d1;


void* connection_matter(void *arg);
 int main () {



    int i;
    pthread_t pth;
    for(i=1;i<=100;i++){
        if(pthread_create(&pth,NULL,&connection_matter,&i)<0){
            perror("Thread making error");
            return 1;
        }
        sleep(1);

    }

    pthread_exit(NULL);


    
     return 0;
 }

void *connection_matter(void* arg){


 char buffer[250];
   
     struct sockaddr_in saddr;
     int fd, ret_val;
     struct hostent *local_host; 

     
     fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
     if (fd == -1) {
         fprintf(stderr, "socket failed [%s]\n", strerror(errno));
         
     }
     printf("Created a socket with fd: %d\n", fd);

     
     saddr.sin_family = AF_INET;         
     saddr.sin_port = 8080;     

     saddr.sin_addr.s_addr=INADDR_ANY;

     
     ret_val = connect(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
     if (ret_val == -1) {
         fprintf(stderr, "connect failed [%s]\n", strerror(errno));
         close(fd);
        
     }
     printf("The Socket is now fully connected\n");

    



    int i=1;
    while(i<=20){
   
    
      buffer[0]=i+'0';
     
     ret_val = send(fd,buffer, sizeof(buffer), 0);
     printf("Successfully sent data (len %d bytes): %d\n", ret_val, buffer[0]-'0');

     sleep(1);

     

     ret_val=read(fd,&d1,sizeof(d1));
     printf("received from server is   %lld\n",d1.buffe[0]);

     
     
     i++;
     }

     close(fd);


}