#ifndef UDP_SERVER_H
#define UDP_SERVER_H

int init_UDP_Server(int *sockfd, int *len, struct sockaddr_in *cliaddr);
int send_UDP_Msg(char *data, int *sockfd, int *len, struct sockaddr_in *cliaddr);

#endif