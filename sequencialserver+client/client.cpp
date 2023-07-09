#include <stdio.h>

#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include<arpa/inet.h>

struct data{

    long long int buffe[1];
    int client_id;
    int port_address;
  


};

struct data d1;

int main()
{

    
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
   


    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
        printf("ERROR opening socket");

    // server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = 8080;
    serv_addr.sin_addr.s_addr=INADDR_ANY;


    
    




    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        printf("ERROR connecting");
    // printf("Please enter the message: ");

    printf("\n");




    int i=1;

    while(i<=20){

        // sleep(10);
        //   bzero(buffer, 256);
    buffer[0]=i+'0';
    // fgets(buffer, 255, stdin);
    n = send(sockfd, buffer, strlen(buffer),0);
    sleep(1);
    if (n < 0)
        printf("ERROR writing to socket");
    bzero(buffer, 256);

    long long int buff[1];

    n = recv(sockfd, &d1, sizeof(d1),0);
    if (n < 0)
        printf("ERROR reading from socket");

    printf("DATA RECEIVED FROM SERVER IS :  ");
    printf("%lld\n", d1.buffe[0]);

    printf("PORT ADDRESS IS : ");

    printf("%d\n",d1.port_address);

    printf("CLIENT ADDRESS : ");
    printf("%d\n",d1.client_id);
    printf("-----------------------\n");
    i++;
    }

  
    return 0;
}