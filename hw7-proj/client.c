#include "csapp.h"

int main(int argc, char **argv) 
{

    int clientfd, port;
    char *host, buf[32];
    rio_t rio;
//char * buf2;


    if (argc != 3) {
fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);


printf("Enter spire id\n");
Fgets(buf,32, stdin);

    clientfd = Open_clientfd(host, port);

//printf("connected\n");

send(clientfd, buf, 32,0);

read(clientfd, buf, 256);
Fputs(buf,stdout);

char want = (char) buf[4];

char * thing ;
thing = &want;


//char test ='7';

//char * test2 = &test;
 

send(clientfd,thing,1,0);

read(clientfd,buf,256);
Fputs(buf,stdout);
//Fgets(buf,8,stdin);
//send(clientfd,buf,8,0);



 
Close(clientfd);
exit(0);   
 }
