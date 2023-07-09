#include <stdio.h>
 #include <netinet/in.h> 
 #include <unistd.h> 
 #include <string.h>
 #include <stdbool.h>
#include <limits.h>
 #include <errno.h>
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
 #define data_buffer 5000

 #define max_numberof_connection 10 

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

 int create_tcp_server_socket() {
     struct sockaddr_in saddr;
     int fd, ret_val;


     fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
     if (fd == -1) {
         fprintf(stderr, "socket failed [%s]\n", strerror(errno));
         return -1;
     }
     printf("Created a socket with fd: %d\n", fd);

   
     saddr.sin_family = AF_INET;         
     saddr.sin_port = 8080;     
     saddr.sin_addr.s_addr = INADDR_ANY; 

  
     ret_val = bind(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
     if (ret_val != 0) {
         fprintf(stderr, "bind failed [%s]\n", strerror(errno));
         close(fd);
         return -1;
     }

     ret_val = listen(fd, 5);
     if (ret_val != 0) {
         fprintf(stderr, "listen failed [%s]\n", strerror(errno));
         close(fd);
         return -1;
     }
     return fd;
 }



 int main () {
     fd_set read_fd_set;
     struct sockaddr_in new_addr;
     int server_fd, new_fd, ret_val, i;
     socklen_t addrlen;
     char buf[250];
     int overall_connections[max_numberof_connection
];

  
     server_fd = create_tcp_server_socket(); 
     if (server_fd == -1) {
       fprintf(stderr, "Failed to create a server\n");
       return -1; 
     }   


     for (i=0;i < max_numberof_connection
;i++) {
         overall_connections[i] = -1;
     }
     overall_connections[0] = server_fd;

     while (1) {
         FD_ZERO(&read_fd_set);
      
         for (i=0;i < max_numberof_connection
    ;i++) {
             if (overall_connections[i] >= 0) {
                 FD_SET(overall_connections[i], &read_fd_set);
             }
         }

       
         printf("\nHere we are using select() for incoming \n");
         ret_val = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);

       
         if (ret_val >= 0 ) {
             printf("Select() returned with the given ret_val%d\n", ret_val);
           
             if (FD_ISSET(server_fd, &read_fd_set)) { 
           
                 printf("Returned fd is %d (server's fd)\n", server_fd);
                 new_fd = accept(server_fd, (struct sockaddr*)&new_addr, &addrlen);
                 if (new_fd >= 0) {
                     printf("Accepted a new connection with fd: %d\n", new_fd);
                     for (i=0;i < max_numberof_connection
                ;i++) {
                         if (overall_connections[i] < 0) {
                             overall_connections[i] = new_fd; 
                             break;
                         }
                     }
                 } else {
                     fprintf(stderr, "accept failed [%s]\n", strerror(errno));
                 }
                 ret_val--;
                 if (!ret_val) continue;
             } 


             for (i=1;i < max_numberof_connection
        ;i++) {
                 if ((overall_connections[i] > 0) &&
                     (FD_ISSET(overall_connections[i], &read_fd_set))) {
                    
                     printf("Returned fd is %d [index, i: %d]\n", overall_connections[i], i);
                     ret_val = recv(overall_connections[i], buf, sizeof(buf), 0);
                  
                     if (ret_val == 0) {
                         printf("Closing connection for fd:%d\n", overall_connections[i]);
                         close(overall_connections[i]);
                         overall_connections[i] = -1;
                     } 
                     if (ret_val > 0) { 
                         printf("Received data (len %d bytes, fd: %d): %d    \n", 
                             ret_val, overall_connections[i], buf[0]-'0');
                           
                            long long int a=factorial(buf[0]-'0');
                             d1.buffe[0]=a;
                            
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
                                
                                fputs("\n",filep);
                                fclose(filep);
                             sleep(0.25);
                                ret_val=send(overall_connections[i],&d1,sizeof(d1),0);
                     } 
                     if (ret_val == -1) {
                         printf("recv() failed for fd: %d [%s]\n", 
                             overall_connections[i], strerror(errno));
                         break;
                     }
                 }
                 ret_val--;
                 if (!ret_val) continue;
             } 
         }
     }

    
     for (i=0;i < max_numberof_connection
;i++) {
         if (overall_connections[i] > 0) {
             close(overall_connections[i]);
         }
     }
     return 0;
 }