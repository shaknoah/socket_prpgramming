
#include <bits/stdc++.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
using namespace std;
#define ull unsigned long long int



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

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{


   
    
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int return_val;


    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    bzero((char *)&serv_addr, sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = 8080;
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        printf("ERROR on binding");
    

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while(1){
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,  (socklen_t *)&clilen);


    int r=1;
    while(r<=20){
            if (newsockfd < 0)
        printf("ERROR on accept");
    bzero(buffer, 256);
    return_val = read(newsockfd, buffer, 255);
   
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

       






    sleep(0.25);
    return_val= write(newsockfd, &d1, sizeof(d1));
    // if (return_val < 0)
    //     error("ERROR writing to socket");


    r++;
    }
    }
    //closing the client
    // fclose(filep);
    close(newsockfd);
    
    return 0;
}