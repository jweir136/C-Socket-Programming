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
    int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
    int numrv;

    // create the listener and retrieve the socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket Sucessfully Retrieved!\n");

    
    memset(&serv_addr, '0', sizeof(serv_addr));

    // initialize all characters in the send data buffer to '0'
    memset(sendBuff, '0', sizeof(sendBuff));

    // tell the listener what protocol to use and what addr and port to
    //      listen to.
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    // bind the listener and the server address info
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // check that the listener is working
    if (listen(listenfd, 10) == -1)
    {
        printf("Failed to Listen\n");
        return -1;
    }

    // continously listen for and accept new incoming connections.
    // copy the desired message into the buffer and send the buffer
    //      to the client.
    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        strcpy(sendBuff, "Message from server");
        write(connfd, sendBuff, strlen(sendBuff));

        close(connfd);
        sleep(1);
    }

    return (0);
}