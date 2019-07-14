/*********************************************************
*           Created by manparvesh on 20/6/18.
 *********************************************************/

#include "client.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        PROXY_PORT = atoi(argv[1]);
    }
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //address of server
    //create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server = gethostbyname(PROXY);
    int iplen = 16;
    char *ip = (char *)malloc(iplen);
    inet_ntop(AF_INET, (void *)server->h_addr_list[0], ip, iplen);

    bzero((sockaddr_in *)&serv_addr, sizeof(sockaddr_in));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PROXY_PORT);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Cannot connect to server");
    }

    pthread_t threads[2];
    pthread_create(&threads[0], nullptr, reader, (void *)sockfd);
    pthread_create(&threads[1], nullptr, writer, (void *)sockfd);
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], nullptr);
    }
    close(sockfd);
    return 0;
}
