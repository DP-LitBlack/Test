// Server side implementation of UDP client-server model 
#include "udp_server.h"

#define PORT     8080 
#define MAXLINE  1024 

static int sockfd; 
static char buffer[MAXLINE]; 
static char *hello = "Hello from server"; 
static struct sockaddr_in servaddr, cliaddr; 
static int len;

// Driver code 
int init_udp() { 
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    int n; 
    
    len = sizeof(cliaddr);  //len is value/result 
    
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    return 1;

}

int send_udp(char *msg) {
    sendto(sockfd, (const char *)msg, strlen(msg),  
    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
        len); 
    // printf("Hello message sent.\n");  
    return 0; 
}