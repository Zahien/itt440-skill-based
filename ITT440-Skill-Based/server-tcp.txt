#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 12345

int main() {
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int generate_random_number_zh;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("SOCKET");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    // Bind socket to the server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("BIND");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(sockfd, 10) < 0) {
        perror("LISTEN");
        exit(1);
    }

    printf("SERVER LISTENING ON PORT %d...\n", PORT);

    // Accept client connection
    addr_size = sizeof(client_addr);
    new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);
    if (new_sockfd < 0) {
        perror("ACCEPT");
        exit(1);
    }

    // Generate a random number between 50000 and 80000
    generate_random_number_zh = rand() % (80000 - 50000 + 1) + 50000;

    // Send the random number to the client
    if (send(new_sockfd, &generate_random_number_zh, sizeof(generate_random_number_zh), 0) < 0) {
        perror("SEND");
        exit(1);
    }

    printf("RANDOM NUMBER %d SENT TO THE CLIENT.\n", generate_random_number_zh);

    // Close the sockets
    close(new_sockfd);
    close(sockfd);

    return 0;
}
