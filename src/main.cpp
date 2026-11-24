#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    using std::cout;
    using std::cin;
    using std::cerr;
    typedef std::string str;

    cout << "MPanel Service Utility - v0.1\n";
    cout << "See https://mpanel.com/ for more information.\n\n";

    int PORT;
    bool askForPort = true;
    for (int i = 1; i < argc; ++i) {
        str curr_arg = argv[i];
        if (curr_arg == "--port" && argc >= i+1) {
            try {
                if (askForPort == false) {
                    cerr << "ERROR: Declared --port <value> more than one time.\n";
                    return 1;
                }
                PORT = std::stoi(argv[++i]);
                askForPort = false;
            } catch (...) {
                cerr << "ERROR: Invalid --port <value> (must be an integer).\n";
                return 1;
            }
        } else {
            cerr << "Usage: MPanel [--port PORT]\n";
            return 1;
        }
    }

    if (askForPort) {
        str input;
        cout << "Enter port: ";
        std::getline(std::cin, input);

        if (input.empty()) {
        std::cerr << "Please specify a port!\n";
        return 1;
    }
    }

    if (PORT < 1 || PORT > 65535) {
        cout << "Invalid port number. Please enter a value between 1 and 65535.\n";
        return 1;
    }
    
    cout << "Starting server on port :" << PORT << "...\n";

    str command = "php -S 0.0.0.0:" + std::to_string(PORT) + " -t web web/router.php";

    return std::system(command.c_str());;
}