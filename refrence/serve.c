#include <sys/types.h>  // system data types time_t
#include <sys/socket.h> //Internet protocol family----socket()
#include <netdb.h>      //hostent structure –official name of host
#include <stdio.h>
#include <string.h>
#include <unistd.h> //fork(), close() etc.
int main()
{
    char str[100];
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);
    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    l
        listen(listen_fd, 10);

    while (1)
    {
        comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
        bzero(str, 100);
        recv(comm_fd, str, 100, 0);

        printf("Echoing back - %s", str);
        send(comm_fd, str, strlen(str), 0);
        close(comm_fd);
    }
}
