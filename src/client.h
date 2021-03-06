/*********************************************************
*           Created by manparvesh on 20/6/18.
 *********************************************************/

#ifndef TUMBICHAT_CLIENT_H
#define TUMBICHAT_CLIENT_H

#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>  //threading
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>  //read and write
#include <map>
#include <string>

#include <arpa/inet.h>  //inet_ntop

#include <iostream>

#define PROXY "127.0.0.1"  //your ip address
int PROXY_PORT = 5000;

using namespace std;

map<int, string> userNameList;

void error(string message) {
    perror(message.c_str());
    exit(1);
}

void *reader(void *param) {
    int socket_fd = (int)param;
    char buffer[1024];
    ssize_t n;
    do {
        bzero(buffer, 1023);
        n = read(socket_fd, buffer, 1023);
        buffer[n] = '\0';
        string username = "";
        if (userNameList.find(socket_fd) != userNameList.end()) {
            username = userNameList[socket_fd];
        }
        printf("\nTumbiChat: %s", buffer);
    } while (n > 0);
    pthread_exit(nullptr);
}

void *writer(void *param) {
    int socket_fd = (int)param;
    char buffer[1024];
    ssize_t n = 0;
    do {
        bzero(buffer, 1023);
        string username = "New user";
        scanf("%[^\n]", buffer);
        if (userNameList.find(socket_fd) == userNameList.end()) {
            username = buffer;
            userNameList[socket_fd] = username;
            cout << "Welcome, " << username << "!!" << endl;
        } else {
            username = userNameList[socket_fd];
        }

        cout << username << "> ";

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

#endif  //TUMBICHAT_CLIENT_H
