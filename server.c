/*
argv[0]-> filename
argv[1]->server_ipaddress
argv[2]->portno
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    // inbuld error function which intreads error number and ouputs the error descirption
    perror(msg);
    // program terminal on occurance of an error
    exit(1);
}

// argv contains fielname and port number
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf("Port number not provided. Program terminated\n");
        exit(1);
    }

    // file descripter,new filedescripter,portno,n->for specific task we result resulted in failure or success
    int sockfd, newsockfd, portno, n;
    // store our buffer and sne it in a data stream
    char buffer[255];

    // sockaddr_in->gives internet addtess of server and clinent it is in netinet file
    struct sockaddr_in serv_addr, cli_addr;

    // socklen_t-> data type in socket.h and it is a 32 bit datatype
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error opening Socket.");
    }
    // clears any data of what ever data it is refering to
    bzero((char *)&serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INDADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Binding Failed");

    // 5 is the no of connections or the backlog
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd < 0)
    {
        error("Error on accept");
    }

    while (1)
    {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
        {
            error("Error on reading");
        }
        printf('Client: %s\n', buffer);
        bzero(buffer, 255);
        // reads bytes from strams
        fgets(buffer, 255, stdin);
        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
            error("Error on Writing.");

        int i = strncmp("Bye", buffer, 3);
        if (i == 0)
            break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
