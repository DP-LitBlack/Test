// Reference: https://www.geeksforgeeks.org/udp-server-client-implementation-c/
// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
    
#define PORT     8080 
#define MAXLINE  1024 


int init_UDP_Server(int *sockfd, int *len, struct sockaddr_in *cliaddr) {

    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr; 

    // Creating socket file descriptor 
    if ( (*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(cliaddr, 0, sizeof(*cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if ( bind(*sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    int n; 
    *len = sizeof(*cliaddr);  //len is value/result 

    n = recvfrom(*sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) cliaddr, 
                (unsigned int *)len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    printf("sockfd : %d\n", *sockfd); 
    return 0;
}

// Driver code 
int send_UDP_Msg(char *data, int *sockfd, int *len, struct sockaddr_in *cliaddr) { 
    sendto(*sockfd, (const char *)data, strlen(data),  
        MSG_CONFIRM, (const struct sockaddr *) cliaddr, 
            *len); 
    printf("Hello message sent.\n");  
    return 0; 
}