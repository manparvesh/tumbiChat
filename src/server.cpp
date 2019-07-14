/*********************************************************
*           Created by manparvesh on 20/6/18.
*********************************************************/

#include "server.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        PROXY_PORT = atoi(argv[1]);
    }

    int socket_fd;
    int new_socket_fd;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    socklen_t client_length = sizeof(client_address);

    // creating a socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        error("Unable to establish socket");
    }

    // fill the sockaddr_in to specify an internet address (where the socket should be bind)
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(static_cast<uint16_t>(PROXY_PORT));
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind created socket to the sockaddr_in
    if (bind(socket_fd, (struct sockaddr *)&server_address,
             sizeof(struct sockaddr)) < 0) {
        error("Unable to bind");
    }

    // listen for clients
    if (listen(socket_fd, 5) < 0) {
        error("Unable to listen for clients");
    }

    // create new socket for each client
    pthread_t threads[MAX_THREADS];
    int number = 0;

    while (number < MAX_THREADS) {
        new_socket_fd = accept(socket_fd, (struct sockaddr *)&client_address,
                               &client_length);
        cout << "new_socket_fd: " << new_socket_fd << endl;
        pthread_create(&threads[number++], nullptr, &process_client, (void *)new_socket_fd);
    }

    for (int i = 0; i < number; i++) {
        pthread_join(threads[i], nullptr);
    }

    close(socket_fd);

    return 0;
}