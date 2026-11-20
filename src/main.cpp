#include <iostream>

int main() {
    using std::cout;
    typedef std::string str;

    cout << "MPanel Service Utility - v0.1\n";
    cout << "See https://mpanel.com/ for more information.\n\n";

    int PORT = 8080;
    bool askForPort = true;
    if (askForPort) {
        cout << "Enter port: ";
        std::cin >> PORT;
    }

    if (PORT < 1 || PORT > 65535) {
        cout << "Invalid port number. Please enter a value between 1 and 65535.\n";
        return 1;
    }
    
    cout << "Starting server on port :" << PORT << "...\n";

    return 0;
}