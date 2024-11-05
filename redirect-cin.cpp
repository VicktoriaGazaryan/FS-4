#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void initialize(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: ./redirect-cin <input-file>\n";
        exit(1);
    }

    const char* filePath = argv[1];
    int fileDescriptor = open(filePath, O_RDONLY);
    if (fileDescriptor == -1) {
        cerr << "Error: Could not open file '" << filePath << "'\n";
        exit(1);
    }

    if (dup2(fileDescriptor, STDIN_FILENO) == -1) {
        cerr << "Error: Failed to redirect standard input\n";
        close(fileDescriptor);
        exit(1);
    }

    close(fileDescriptor);
}

int main(int argc, char** argv) {
    initialize(argc, argv);

    string input;
    cin >> input;

    string reversed(input.rbegin(), input.rend());

    cout << reversed << endl;

    return 0;
}
