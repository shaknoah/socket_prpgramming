/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define ull unsigned long long int

int n;
 char buffer[256];


ull factorial(int n)
{
 
 
    ull ans = 1; 
 
    
    for (ull i = 2; i <= n; i++)
        ans *= i;
 
    return ans;
}



struct data{

    long long int buffe[1];
    int client_id;
    int port_address;
   



};

struct data d1;

struct used{
    int newsockfd;
    
    struct sockaddr_in cli_addr;
};





void* helper(void *arg){
   
    int newsockfd=((struct used *)arg)->newsockfd;
   
    struct sockaddr_in cli_addr=((struct used *)arg)->cli_addr;
    
     int r=1;
    while(r<=20){
            if (newsockfd < 0)
        printf("ERROR on accept");
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0)
        printf("ERROR reading from socket");
    printf("Here is the message: %d\n", buffer[0]-'0');


    d1.buffe[0]=factorial( buffer[0]-'0');
   
    d1.client_id=buffer[0]-'0';
    d1.port_address=htons(cli_addr.sin_port);



    // sleep(1);
    n = write(newsockfd, &d1, sizeof(d1));
    if (n < 0)
        printf("ERROR writing to socket");


    r++;
    }
}
 



int main()
{


    struct used us1;
    

 int sockfd, newsockfd,clilen;

struct sockaddr_in serv_addr, cli_addr;


    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     


    if (sockfd < 0)
        printf("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    // portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = 8080;
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        printf("ERROR on binding");
    

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
   

    while(1){
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
     us1.newsockfd=newsockfd;
     us1.cli_addr=cli_addr;

    pthread_t th;

    
            if(pthread_create(&th,NULL,&helper,&us1)!=0){
        perror("Failed to created thread");


    // if(pthread_join(th,NULL)!=0){
    //     perror("Failed to join the thread   ");
    // }
    }
    
  
    
    





   
    }
      close(newsockfd);
    //closing the client

    
    return 0;
}