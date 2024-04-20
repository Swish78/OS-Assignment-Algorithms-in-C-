#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

#define el "\n"
#define td "\t"
#define line "----------------------"

int twoWayCommunication() {
    int fromChild[2], toChild[2];
	
    if (pipe(fromChild) == -1 || pipe(toChild) == -1) {
        cout << "pipe failed" << el;
        return 1;
    }
	
    int id = fork();
	
    if (id == -1) {
        cout << "fork failed" << el;
        return 2;
    }
	
    if (id == 0) {
        // Child process
        close(toChild[1]);
        close(fromChild[0]);
		
        char s1[100], s2[100];
		
        if (read(toChild[0], &s1, sizeof(s1)) == -1) {
            cout << "read failed" << el;
            return 3;
        }
		
        cout << "(CHILD)---> received from parent: " << s1 << el;
        cout << "(CHILD)----> enter the string to be concatenated with the string got from parent: ";
        cin >> s2;
		
        strcat(s1, " ");
        strcat(s1, s2);
		
        if (write(fromChild[1], &s1, sizeof(s1)) == -1) {
            cout << "write failed" << el;
            return 4;
        }
		
        close(toChild[0]);
        close(fromChild[1]);
    } else {
        close(toChild[0]);
        close(fromChild[1]);
		
        char s1[100];
		
        cout << "(PARENT) --> enter the string: ";
        cin >> s1;
		
        if (write(toChild[1], &s1, sizeof(s1)) == -1) {
            cout << "write failed" << el;
            return 5;
        }
		
        if (read(fromChild[0], &s1, sizeof(s1)) == -1) {
            cout << "read failed" << el;
            return 6;
        }
		
        cout << "(PARENT)---> received from child: " << s1 << el;
		
        close(toChild[1]);
        close(fromChild[0]);
    }
	
    return 2;
}

int oneWayCommunication() {
    int fd[2];
	
    if (pipe(fd) == -1) {
        cout << "pipe failed" << el;
        return 1;
    }
	
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int start, end, sum = 0;
	
    int id = fork();
	
    if (id == -1) {
        cout << "fork failed" << el;
        return 2;
    }
	
    start = (id == 0) ? 0 : n / 2;
    end = (id == 0) ? n / 2 : n;
	
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
	
    if (id == 0) {
        close(fd[0]);
		
        if (write(fd[1], &sum, sizeof(sum)) == -1) {
            cout << "Write failed" << el;
            return 3;
        }
		
        close(fd[1]);
    } else {
        int pSum;
        close(fd[1]);
		
        if (read(fd[0], &pSum, sizeof(pSum)) == -1) {
            cout << "read failed" << el;
            return 3;
        }
		
        cout << "Sum of complete array is: " << (sum + pSum) << el;
        close(fd[0]);
    }
	
    return 5;
}

int main() {
    int choice;
	
    cout << "Enter 1 for one way communication:" << el;
    cout << "Enter 2 for two way communication:" << el;
    cin >> choice;
	
    cout << line << el;
	
    if (choice == 1) {
        oneWayCommunication();
    } else if (choice == 2) {
        twoWayCommunication();
    }
	
    cout << line << el;
	
    return 0;
}
