#include <bits/stdc++.h>

//need to add sys/wait.h
#include <sys/wait.h>
using namespace std;

int main(int count, char *argv[]) {
    // Fork a new process
    pid_t p = fork();


    if (p < 0) {
        cout << "Fork Unsuccessful\n";
        exit(0);
    } else if (p == 0) {
        
        string option = argv[1];

        if (option == "cp") {
            
            execlp("/bin/cp", "cp", argv[2], argv[3], NULL);
        } else if (option == "ls") {
           
            execlp("/bin/ls", "ls", NULL);
        } else if (option == "grep") {
           
            execlp("/bin/grep", "grep", argv[2], argv[3], argv[4], NULL);
        }
    }

    cout << "Parent Process ID: " << getpid() << endl;
    cout << "Child Process ID: " << p << endl;
   
    waitpid(p, NULL, 0); 
    cout << "Child process completed\n";

    return 0;
}
