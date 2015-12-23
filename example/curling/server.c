#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define CHUNK_SIZE 256
#define CONNECTION_CLOSE "Connection: close\n"

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

void close_connection(int request) {
    if ((write(request, CONNECTION_CLOSE, sizeof(CONNECTION_CLOSE))) == -1) {
        printf("Failed to send Connection: close");
    } else {
        printf("Close connection.");
    }
}

void service_request(int request) {
    char* buffer = malloc(CHUNK_SIZE*sizeof(char));
    ssize_t bytes_read;
    while ((bytes_read = read(request, buffer, sizeof(buffer))) > 1) {
        for (int character=0; character < bytes_read; character++) {
            printf("%c", *(buffer + character));
        }
    }
    if (bytes_read == -1) {
        printf("Error occurred reading request file descriptor. %i", errno);
    }
    close_connection(request);
}

int main() {
    int socket_fd = get_socket_fd();
    struct sockaddr_in address = get_address("127.0.0.1", 8080);
    bind_socket_to_address(socket_fd, address);
    listen(socket_fd, 10);
    socklen_t remoteaddr_len;
    int request;
    while (1) {
        if ((request = accept(socket_fd, 0, 0)) == -1) {
            printf("Failed to accept incoming request.");
        } else {
            printf("Received incoming request.\n");
            service_request(request);
            close(request);
        }
    }
    return 0;
}