#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;

#define el "\n"
#define td "\t"

int main() {
    int fd[2];
    pid_t pid;
    char buffer[1024];

    cout << "----------------------------------------------" << el;
    cout << "Inter-Process Communication using Pipes" << el;
    cout << "----------------------------------------------" << el;

    if (pipe(fd) == -1) {
        cout << "Error creating pipe" << el;
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        cout << "Error creating child process" << el;
        return 1;
    } else if (pid == 0) { // Child process
        close(fd[1]); // Close the write end of the pipe

        int bytes_read = read(fd[0], buffer, 1024);
        if (bytes_read == -1) {
            cout << "Error reading from pipe" << el;
            return 1;
        }

        cout << "Child process received message: " << buffer << el;
        close(fd[0]); // Close the read end of the pipe
    } else { // Parent process
        close(fd[0]); // Close the read end of the pipe

        const char* message = "Hello from parent process!";
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]); // Close the write end of the pipe

        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish
    }

    cout << "----------------------------------------------" << el;
    return 0;
}