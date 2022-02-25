#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(void)
{
    // Set all the system variables
    int sockfd = 0;
    int n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;

    memset(recvBuff, '0', sizeof(recvBuff));

    // create the client socket and check if it works.
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error: Failed to create socket\n");
        return 1;
    }

    // assign protocol, address, and port to the client socket.
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect to the server and check that the conection worked
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Error: failed to connect\n");
        return 1;
    }

    // read bytes as they are incoming, and add them to the buffer.
    while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0)
    {
        recvBuff[n] = 0;

        if (fputs(recvBuff, stdout) == EOF)
            printf("Error: Fputs Error\n");
        
        printf("\n");
    }

    if (n < 0)
        printf("Read Error\n");

    return (0);
}