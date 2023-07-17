#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define number_children_zh 3

int main() {
    pid_t pid[number_children_zh];
    int fd[number_children_zh][2]; // File descriptors for pipes

    // Create pipes for communication
    for (int i = 0; i < number_children_zh; i++) {
        if (pipe(fd[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Create child processes
    for (int i = 0; i < number_children_zh; i++) {
        pid[i] = fork();

        if (pid[i] < 0) {
            perror("fork");
            exit(1);
        } else if (pid[i] == 0) {
            // Child process
            close(fd[i][1]); // Close the write end of the pipe

            char message_zh[50];
            read(fd[i][0], message_zh, sizeof(message_zh));
            printf("CHILD %d received message: %s\n", i + 1, message_zh);

            printf("CHILD %d interrupted!\n", i + 1);
            exit(0);
        } else {
            // Parent process
            close(fd[i][0]); // Close the read end of the pipe

            // Send message to child process
            char message_from_parent_zh[50];
            sprintf(message_from_parent_zh, "Hello from PARENT to CHILD %d", i + 1);
            write(fd[i][1], message_from_parent_zh, sizeof(message_from_parent_zh));
            close(fd[i][1]); // Close the write end after sending

            // Wait for child process to finish
            wait(NULL);
        }
    }

    return 0;
}
