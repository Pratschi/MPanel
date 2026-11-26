#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    using std::cout;
    using std::cin;
    using std::cerr;
    typedef std::string str;

    str const VERSION = "0.1.1";

    int DEBUGMODE = false;
    int VERSION_STATUS = 0;
    int PORT;
    str phpPath = "php";
    bool askForPort = true;

    for (int i = 1; i < argc; ++i) {
        if (str(argv[i]) == "--debug") {
            if (!DEBUGMODE) {DEBUGMODE = true;
            } else {cerr << "ERROR: Declared --debug more than one time.\n";return 1;}
        } else if (str(argv[i]) == "--version") {
            if (VERSION_STATUS == 0) {VERSION_STATUS = 1;} /* --version detected */
            else if (VERSION_STATUS == 2) {VERSION_STATUS = 3; break;} /* ERROR (args + --version) */
        } else {
            if (VERSION_STATUS == 1) {VERSION_STATUS = 3; break;} /* ERROR (args + --version) */
            else {VERSION_STATUS = 2;} /* args detected */
        }
    }

    if (VERSION_STATUS == 1) {cout << "MPanel v" + VERSION + "\n"; return 0;}
    if (DEBUGMODE) {cout << "VERSION STATUS: " << std::to_string(VERSION_STATUS) + "\n";}
    cout << "MPanel Service Utility - v" + VERSION + "\n";
    cout << "See https://mpanel.com/ for more information.\n\n";

    if (DEBUGMODE) {cout << "\n===== DEBUG MODE ENABLED =====\n";}
    if (VERSION_STATUS == 3) {cerr << "ERROR: No parameters expected alongside --version (except --debug)\n"; return 1;}

    for (int i = 1; i < argc; ++i) {
        str curr_arg = argv[i];
        if (DEBUGMODE) {cout << "[DEBUG] ARG[" + std::to_string(i) + "] = " + curr_arg;}

        if (curr_arg == "--port") {
            if (!argc >= i+1) {cerr << "ERROR: --port argument requires a value (<PORT>).\n";}
            try {
                if (askForPort == false) {cerr << "ERROR: Declared --port <PORT> more than one time.\n";return 1;}
                PORT = std::stoi(argv[++i]);
                if (DEBUGMODE) {cout << " <" + std::to_string(PORT) + ">";}
                askForPort = false;
            } catch (...) {cerr << "ERROR: Invalid --port <PORT> (must be an integer).\n";return 1;}

        } else if (curr_arg == "--custom-php") {
            if (!argc >= i+1) {cerr << "ERROR: --custom-php argument requires a value (<PATH>).\n";return 1;}
            phpPath = argv[++i];
            if (DEBUGMODE) {cout << " <" + phpPath + ">";}
        } else if (curr_arg == "--debug") {
        } else {cerr << "Usage: MPanel [--port PORT] [--custom-php PATH]\n";return 1;
        }

        if (DEBUGMODE) {cout << "\n";}
    }

    if (askForPort) {
        str input;cout << "Enter port: ";std::getline(std::cin, input);
        if (input.empty()) {cerr << "Please specify a port!\n";return 1;}
        PORT = std::stoi(input);
    }

    if (PORT < 1 || PORT > 65535) {
        cerr << "ERROR: Invalid port number. Please enter a value between 1 and 65535.\n";
        return 1;
    }
    
    cout << "Starting server on port :" << PORT << "...\n\n";

    int phpStatus = std::system("php --version >/dev/null 2>&1");
    if (phpStatus != 0) {
        cerr << "ERROR: Could not access PHP (is it installed and in PATH?).\n";
        cout << "To use a custom PHP Path, use --custom-php <PATH>.\n";
        return 1;
    }

    str command = "php -S 0.0.0.0:" + std::to_string(PORT) + " -t web web/router.php";

    return std::system(command.c_str());;
}