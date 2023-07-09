 #include <stdio.h>
 #include <errno.h>
 #include <netinet/in.h> 
 #include <netdb.h> 
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<pthread.h>

//  #define DATA_BUFFER "Mona Lisa was painted by Leonardo da Vinci"
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

 void* connection_matter(void *arg){

     char DATA_BUFFER[250];
   
     struct sockaddr_in saddr;
     int sock_fd, ret_val;
     struct hostent *local_host;

    
     sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
   
     printf("Created a socket with sock_fd: %d\n", sock_fd);

   
     saddr.sin_family = AF_INET;         
     saddr.sin_port = 8080;     
    
     saddr.sin_addr.s_addr=INADDR_ANY;

     
     ret_val = connect(sock_fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
     if (ret_val == -1) {
         fprintf(stderr, "connect failed [%s]\n", strerror(errno));
         close(sock_fd);
      
     }
     printf("The Socket is  connected   now \n");




    int k=1;

    while(k<=20){
   
      DATA_BUFFER[0]=k+'0';
     
     ret_val = send(sock_fd,DATA_BUFFER, sizeof(DATA_BUFFER), 0);
     printf("Successfully sent data (len %d bytes): %d\n", ret_val, DATA_BUFFER[0]-'0');

     sleep(1);

    long long int ans[1];

    ret_val=recv(sock_fd,&d1,sizeof(d1),0);
    printf("Message from server is     :  %lld\n",d1.buffe[0]);

            k++;
    }

    
     close(sock_fd);
 }