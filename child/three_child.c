#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num_children = 3;
    int i;
    pid_t child_pid;

    for (i = 0; i < num_children; ++i) {
        if ((child_pid = fork()) == 0) {
            // 子進程執行的工作
            printf("Child %d: Hello from child process!\n", i + 1);
            exit(0); // 子進程執行完畢後退出
        }
    }

    // 等待所有子進程完成
    int status;
    for (i = 0; i < num_children; ++i) {
        wait(&status);
    }

    // 父進程執行的工作
    printf("Parent: All child processes have finished.\n");

    return 0;
}
