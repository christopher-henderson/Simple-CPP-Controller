#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int get_socket_fd(void) {
    int socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // Should dispatch to errno interpeter for descriptive errors.
        printf("%i\n", errno);
        abort();
    }
    return socket_fd;
}

struct sockaddr_in get_address(char* host, int port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    inet_aton(host, (struct in_addr*) &address.sin_addr.s_addr);
    return address;
}

void bind_socket_to_address(int socket, struct sockaddr_in address) {
    if (bind(socket, (struct sockaddr*) &address, sizeof(address)) < 0) {
        // Should dispatch to errno interpeter for descriptive errors.
        printf("BIND FAILURE %i\n", errno);
        abort();
    }
    return;
}

int main() {
    int socket_fd = get_socket_fd();
    struct sockaddr_in address = get_address("127.0.0.1", 8080);
    bind_socket_to_address(socket_fd, address);
    listen(socket_fd, 10);
    socklen_t remoteaddr_len;
    while (1) {
        int c = accept(socket_fd, 0, 0);
        printf("LOL!\n");
    }

    return 0;
}