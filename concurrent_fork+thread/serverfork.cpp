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
#define ull unsigned long long int
using namespace std;



struct data{

    long long int buffe[1];
    int client_id;
    int port_address;
    



};

struct data d1;
 

ull factorial(int n)
{
 
 
    ull ans = 1; 
 
    
    for (ull i = 2; i <= n; i++)
        ans *= i;
 
    return ans;
}



int main()
{

    int pid;
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        printf("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = 8080;
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        printf("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
   while (1) {
         newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr,(socklen_t *)&clilen);
         if (newsockfd < 0) 
             printf("ERROR on accept");
         pid = fork();
         if (pid < 0)
             printf("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
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
                 char arr[12], *p = arr + 11;
                    *p = 0;
                    *p=d1.buffe[0];
                
        string str=to_string(d1.buffe[0]);
        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
        string str1=to_string(d1.port_address);
        char *cstr1=new char[str1.length()+1];
        FILE* filep;
    filep=fopen("dataget.txt","a+");
        fputs("Data sent is  : ",filep);
        fputs(cstr,filep);
  
         fputs("\n",filep);
          fputs("Client IP address is  : ",filep);
           fputs(inet_ntoa(cli_addr.sin_addr),filep);
           fputs("\n",filep);
           
           fputs("Client port address is  :  ",filep);
           fputs(cstr1,filep);
           fputs("\n",filep);
        fclose(filep);


                
            
                n = write(newsockfd, &d1, sizeof(d1));
                if (n < 0)
                    printf("ERROR writing to socket");


                r++;
                }
    
         
             exit(0);
         }
         else close(newsockfd);
     }


    
    return 0;
}