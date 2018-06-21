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
#include <map>

using namespace std;

int PROXY_PORT = 5000;

map<int, string> usernames;

void error(string message) {
    perror(message.c_str());
    exit(1);
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


void *reader(void *parameters) {
    int socket_fd = (int) parameters;
    char buffer[BUFFER_SIZE];
    ssize_t n;

    do {
        bzero(buffer, BUFFER_MAX_INDEX);
        n = read(socket_fd, buffer, BUFFER_MAX_INDEX);

        buffer[n] = '\0';
        string username = "New User";
        string buffer_string(buffer);
        if (usernames.find(socket_fd) == usernames.end()){
            buffer_string.erase(buffer_string.find_last_not_of("\n") + 1);
            username = buffer_string;
            usernames[socket_fd] = username;
            cout << "New user added: " << username << endl;
            char welcome_message[BUFFER_SIZE];
            sprintf(welcome_message, "Welcome, %s!!\n", username.c_str());
            n = write(socket_fd, welcome_message, strlen(welcome_message));
            pthread_t threads[1];
            pthread_create(&threads[0], nullptr, writer, (void *) socket_fd);
            pthread_join(threads[0], nullptr);
            FLUSH;
            // close(socket_fd);
        } else {
            username = usernames[socket_fd];
            cout << socket_fd << ":" << username << ": " << buffer_string << endl;
        }
    } while (n > 0);

    pthread_exit(nullptr);
}

void *process_client(void *args) {
    FLUSH;
    ssize_t n;
    int new_socket_fd = (int) args;

    char send[MESSAGE_SIZE];
    bzero(send, MESSAGE_SIZE);

    char receive[MESSAGE_SIZE];
    bzero(receive, MESSAGE_SIZE);

    sprintf(send, "\n"
                  "::::::::::: :::    ::: ::::    ::::  :::::::::  ::::::::::: \n"
                  "    :+:     :+:    :+: +:+:+: :+:+:+ :+:    :+:     :+:     \n"
                  "    +:+     +:+    +:+ +:+ +:+:+ +:+ +:+    +:+     +:+     \n"
                  "    +#+     +#+    +:+ +#+  +:+  +#+ +#++:++#+      +#+     \n"
                  "    +#+     +#+    +#+ +#+       +#+ +#+    +#+     +#+     \n"
                  "    #+#     #+#    #+# #+#       #+# #+#    #+#     #+#     \n"
                  "    ###      ########  ###       ### #########  ########### \n"
                  "Welcome to TumbiChat! Please enter your preferred username:\n");

    n = write(new_socket_fd, send, strlen(send));

    pthread_t threads[2];
    pthread_create(&threads[0], nullptr, reader, (void *) new_socket_fd);
    pthread_create(&threads[1], nullptr, writer, (void *) new_socket_fd);

    pthread_join(threads[0], nullptr);
    pthread_join(threads[1], nullptr);

    FLUSH;
    close(new_socket_fd);

    pthread_exit(nullptr);
}


#endif //TUMBICHAT_SERVER_H
