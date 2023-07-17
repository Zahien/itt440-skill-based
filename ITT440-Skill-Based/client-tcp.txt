#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int generate_random_number_zh;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.116.128");
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    // Receive the random number from the server
    if (recv(sockfd, &generate_random_number_zh, sizeof(generate_random_number_zh), 0) < 0) {
        perror("recv");
        exit(1);
    }

    printf("Random number received from the server: %d\n", generate_random_number_zh);

    // Close the socket
    close(sockfd);

    return 0;
}
