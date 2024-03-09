#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARRAY_SIZE 300
#define NUM_PROCESSES 3

void initialize_array(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = 1;
    }
}

int compute_partial_sum(int *arr, int start, int end) {
    int partial_sum = 0;
    for (int i = start; i < end; ++i) {
        partial_sum += arr[i];
    }
    return partial_sum;
}

int main() {
    int my_array[ARRAY_SIZE];
    int segment_size = ARRAY_SIZE / NUM_PROCESSES;
    int segments[NUM_PROCESSES][2]; // [start, end] indices for each segment

    // Create an array of 300 elements, all initialized to 1
    initialize_array(my_array, ARRAY_SIZE);

    // Divide the array into equal segments for each child process
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        segments[i][0] = i * segment_size;
        segments[i][1] = (i + 1) * segment_size;
    }

    // Create child processes
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            int partial_sum = compute_partial_sum(my_array, segments[i][0], segments[i][1]);
            printf("num:%d child sum %d \n",i ,partial_sum);
            exit(partial_sum);
        } else if (pid < 0) {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all child processes to finish
    int total_sum = 0;
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        int status;
        wait(&status);
        total_sum += WEXITSTATUS(status);
    }

    // Output the total sum
    printf("Total sum of the array: %d\n", total_sum);

    return 0;
}
