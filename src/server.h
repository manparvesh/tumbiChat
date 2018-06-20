/*********************************************************
*           Created by manparvesh on 20/6/18.
 *********************************************************/

#ifndef TUMBICHAT_SERVER_H
#define TUMBICHAT_SERVER_H

#include<iostream>
#include<cstdio>
#include<sys/types.h>
#include<cstdlib>
#include<string.h>
#include<string>
#include<unistd.h>
#include<netinet/in.h> // for struct sockaddr_in
#include<sys/socket.h> //for socket() and Defined constants
#include<netdb.h>
#include<arpa/inet.h>
#include<pthread.h> //threading
#include<map>

#include<ctype.h>

#define MAX_THREADS 100
#define BUFFER_SIZE 1024
#define BUFFER_MAX_INDEX 1023
#define FLUSH  {fflush(stdout);}
#define MESSAGE_SIZE 256

#include<vector>

using namespace std;

int PROXY_PORT = 5000;

void error(string message) {
    perror(message.c_str());
    exit(1);
}

void *reader(void *parameters) {
    int socket_fd = (int) parameters;
    char buffer[BUFFER_SIZE];
    ssize_t n;

    do {
        bzero(buffer, BUFFER_MAX_INDEX);
        n = read(socket_fd, buffer, BUFFER_MAX_INDEX);

        buffer[n] = '\0';
        printf("Other: %s", buffer);
    } while (n > 0);

    pthread_exit(nullptr);
}

void *writer(void *parameters) {
    int socket_fd = (int) parameters;
    char buffer[BUFFER_SIZE];
    ssize_t n = 0;

    do {
        bzero(buffer, BUFFER_MAX_INDEX);
        scanf("%[^\n]", buffer);
        getchar();
        size_t len = strlen(buffer);
        if (len > 0) {
            buffer[len] = '\n';
            buffer[len + 1] = '\0';
            n = write(socket_fd, buffer, strlen(buffer));
        }
    } while (n > 0);

    pthread_exit(nullptr);
}

void *process_client(void *args) {
    FLUSH;
    ssize_t n;
    int new_socket_fd = (int) args;

    char send[MESSAGE_SIZE];
    char receive[MESSAGE_SIZE];
    bzero(send, MESSAGE_SIZE);
    bzero(receive, MESSAGE_SIZE);

    sprintf(send, "Welcome to TumbiChat!\n");

    n = write(new_socket_fd, send, strlen(send));

    pthread_t threads[2];
    pthread_create( &threads[0] , nullptr, reader , (void*) new_socket_fd);
    pthread_create( &threads[1] , nullptr, writer , (void*) new_socket_fd);

    pthread_join( threads[0], nullptr);
    pthread_join( threads[1], nullptr);

    FLUSH;
    close(new_socket_fd);

    pthread_exit(nullptr);
}


#endif //TUMBICHAT_SERVER_H
