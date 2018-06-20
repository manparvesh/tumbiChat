/*********************************************************
*           Created by manparvesh on 20/6/18.
 *********************************************************/

#ifndef TUMBICHAT_CLIENT_H
#define TUMBICHAT_CLIENT_H


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> //read and write
#include<netinet/in.h>
#include<sys/socket.h>
#include<netdb.h>
#include<pthread.h> //threading

#include<arpa/inet.h> //inet_ntop

#include<iostream>

#define PROXY "127.0.0.1" //your ip address
int PROXY_PORT = 5000;

using namespace std;

void error(string message) {
    perror(message.c_str());
    exit(1);
}

void *reader(void *param) {
    int sockfd = (int) param;
    char buffer[1024];
    ssize_t n;
    do {
        bzero(buffer, 1023);
        n = read(sockfd, buffer, 1023);
        buffer[n] = '\0';
        printf("Other: %s", buffer);
    } while (n > 0);
    pthread_exit(nullptr);
}

void *writer(void *param) {
    int sockfd = (int) param;
    char buffer[1024];
    ssize_t n = 0;
    do {
        bzero(buffer, 1023);
        scanf("%[^\n]", buffer);
        getchar();
        size_t len = strlen(buffer);
        if (len > 0) {
            buffer[len] = '\n';
            buffer[len + 1] = '\0';
            n = write(sockfd, buffer, strlen(buffer));
        }
    } while (n > 0);
    pthread_exit(nullptr);
}


#endif //TUMBICHAT_CLIENT_H
