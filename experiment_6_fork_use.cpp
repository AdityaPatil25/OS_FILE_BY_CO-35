#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    cout << "Parent process: My PID is " << getpid() << endl;

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Error: Fork failed" << endl;
        return 1;
    } else if (pid == 0) {
        // This code is executed by the child process
        cout << "Child process: My PID is " << getpid() << endl;
        cout << "Child process: My parent's PID is " << getppid() << endl;
        cout << "Child process: Hello from the child!" << endl;
    } else {
        // This code is executed by the parent process
        cout << "Parent process: I have a child with PID " << pid << endl;
        cout << "Parent process: Hello from the parent!" << endl;
    }

    return 0;
}
