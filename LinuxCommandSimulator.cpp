#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h> // for fork, execlp
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <command> [args...]" << endl;
        return 1;
    }

    pid_t p = fork();

    if (p < 0) {
        cerr << "Fork Unsuccessful" << endl;
        exit(1);
    } else if (p == 0) {
        string option = argv[1];

        if (option == "cp" && argc >= 4) {
            execlp("/bin/cp", "cp", argv[2], argv[3], (char *)NULL);
        } else if (option == "ls") {
            execlp("/bin/ls", "ls", (char *)NULL);
        } else if (option == "grep" && argc >= 5) {
            execlp("/bin/grep", "grep", argv[2], argv[3], argv[4], (char *)NULL);
        } else {
            cerr << "Invalid option or insufficient arguments" << endl;
            exit(1);
        }
    }

    cout << "Parent Process ID: " << getpid() << endl;
    cout << "Child Process ID: " << p << endl;

    waitpid(p, NULL, 0);
    cout << "Child process completed" << endl;

    return 0;
}
