#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2]; // Declare an array to hold file descriptors for the pipe
    int pid;

    if (pipe(fd) == -1) {
        printf("Error opening pipe.\n");
        exit(-1);
    }

    if ((pid = fork()) == 0) { // Child process
        close(fd[0]); // Close the read end of the pipe
        int x;
        printf("Enter an integer number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int)); // Write the integer to the pipe
        close(fd[1]); // Close the write end of the pipe
    } else { // Parent process
        close(fd[1]); // Close the write end of the pipe
        int y;
        read(fd[0], &y, sizeof(int)); // Read the integer from the pipe
        printf("Parent received number: %d\n", y);
        close(fd[0]); // Close the read end of the pipe
    }

    return 0;
}
