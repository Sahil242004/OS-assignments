#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; // pipefd[0] - read end, pipefd[1] - write end
    pid_t pid;
    char buffer[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close unused write end

        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(pipefd[0]);
    } else {
        // Parent process
        close(pipefd[0]); // Close unused read end

        char message[] = "Hello from parent";
        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]);
        wait(NULL); // Wait for child to finish
    }

    return 0;
}
