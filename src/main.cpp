#include <iostream>
#include <cstdlib>
#include <string>

#include "embedded_web.hpp"
#include <filesystem>
#include <fstream>

/* CRASH HANDLER */
#ifdef _WIN32
const std::string nullDevice = "NUL";
#include <io.h>
#define IS_INTERACTIVE() (_isatty(_fileno(stdin)))
#else
const std::string nullDevice = "/dev/null";
#include <unistd.h>
#define IS_INTERACTIVE() (isatty(STDIN_FILENO))
#endif





void reportError(const std::string& message) {
    using namespace std;
    cerr << message << '\n';

    if (IS_INTERACTIVE()) {
        cerr << "\nPress Enter to close...";
        string unused;
        getline(std::cin, unused);
    }
}





int main(int argc, char* argv[]) {
    using std::cout;
    typedef std::string str;

    str const VERSION = "0.2.1";

    int DEBUGMODE = false;
    int VERSION_STATUS = 0;
    int PORT;
    str phpPath = "";
    str webPath = "";
    str HOST = "";
    bool askForPort = true;





    /* =========== SPECIAL ARGS ========== */

    for (int i = 1; i < argc; ++i) {
        if (str(argv[i]) == "--debug") {
            if (!DEBUGMODE) {DEBUGMODE = true;
            } else {reportError("ERROR: Declared --debug more than one time.\n");return 1;}
        } else if (str(argv[i]) == "--version") {
            if (VERSION_STATUS == 0) {VERSION_STATUS = 1;} /* --version detected */
            else if (VERSION_STATUS == 2) {VERSION_STATUS = 3; break;} /* ERROR (args + --version) */
        } else {
            if (VERSION_STATUS == 1) {VERSION_STATUS = 3; break;} /* ERROR (args + --version) */
            else {VERSION_STATUS = 2;} /* args detected */
        }
    }





    /* =========== INITIALIZATION ========== */

    if (DEBUGMODE) {cout << "VERSION STATUS: " << std::to_string(VERSION_STATUS) + "\n";}
    if (VERSION_STATUS == 1) {cout << "MPanel v" + VERSION + "\n"; return 0;}
    cout << "MPanel Service Utility - v" + VERSION + "\n";
    cout << "See https://mpanel.com/ for more information.\n\n";

    if (DEBUGMODE) {cout << "\n===== DEBUG MODE ENABLED =====\n";}
    if (VERSION_STATUS == 3) {reportError("ERROR: No parameters expected alongside --version (except --debug)\n"); return 1;}





    /* =========== ARG MANAGEMENT ========== */
    
    for (int i = 1; i < argc; ++i) {
        str curr_arg = argv[i];
        if (DEBUGMODE) {cout << "[DEBUG] ARG[" + std::to_string(i) + "] = " + curr_arg;}

        if (curr_arg == "--port") {
            if (!argc >= i+1) {reportError("ERROR: --port argument requires a value (<PORT>).\n");}
            try {
                if (askForPort == false) {reportError("ERROR: Declared --port <PORT> more than one time.\n");return 1;}
                PORT = std::stoi(argv[++i]);
                if (DEBUGMODE) {cout << " <" + std::to_string(PORT) + ">";}
                askForPort = false;
            } catch (...) {reportError("ERROR: Invalid --port <PORT> (must be an integer).\n");return 1;}

        } else if (curr_arg == "--custom-php") {
            if (!argc >= i+1) {reportError("ERROR: --custom-php argument requires a value (<PATH>).\n");return 1;}
            phpPath = argv[++i];
            if (DEBUGMODE) {cout << " <" + phpPath + ">";}
        } else if (curr_arg == "--debug") {
        } else if (curr_arg == "--custom-web") {
            if (!argc >= i+1) {reportError("ERROR: --web argument requires a value (<PATH>).\n");}
            try {
                if (webPath != "") {reportError("ERROR: Declared --web <PATH> more than one time.\n");return 1;}
                webPath = argv[++i];
                if (DEBUGMODE) {cout << " <" + webPath + ">";}
            } catch (...) {reportError("ERROR: Invalid --web <PATH> (must be a valid Path).\n");return 1;}
        } else if (curr_arg == "--host") {
            if (!argc >= i+1) {reportError("ERROR: --host argument requires a value (<ADRESS>).\n");}
            try {
                if (HOST != "") {reportError( "ERROR: Declared --host <ADRESS> more than one time.\n");return 1;}
                HOST = argv[++i];
                if (DEBUGMODE) {cout << " <" + HOST + ">";}
            } catch (...) {reportError("ERROR: Invalid --host <ADRESS> (must be a valid Adress).\n");return 1;}
        } else {reportError("Usage: MPanel [--port PORT] [--host ADRESS] [--custom-php PATH] [--custom-web PATH] [--debug]\n");return 1;
        }

        if (DEBUGMODE) {cout << "\n";}
    } if (DEBUGMODE) {cout << "\n";}





    /* =========== PORT MANAGEMENT ========== */

    if (askForPort) {
        str input;cout << "Enter port: ";std::getline(std::cin, input);
        if (input.empty()) {reportError("Please specify a port!\n");return 1;}
        try {PORT = std::stoi(input);
        } catch(...) {reportError("ERROR: Invalid port (must be an integer).\n");return 1;}
    }

    if (PORT < 1 || PORT > 65535) {reportError("ERROR: Invalid port number. Please enter a value between 1 and 65535.\n");return 1;}




    
    /* =========== WEBSITE FILE EXTRACTION ========== */

    namespace fs = std::filesystem;
    fs::path tempRoot;fs::path webRoot; // Avoid Undefined Errors!
    
    if (webPath != "") {
        webRoot = webPath;
    } else {
        tempRoot = fs::temp_directory_path() /("MPanel-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        webRoot = tempRoot / "web";
        try {
            for (const auto& asset : embedded_web::assets) {
                fs::path outputPath = webRoot / asset.path;
                fs::create_directories(outputPath.parent_path());

                std::ofstream output(outputPath, std::ios::binary);
                if (!output) {fs::remove_all(tempRoot);reportError("ERROR: Could not access Temp Directory to server Website.\nMake sure MPanel has the correct permissions.");return 1;}
                output.write(asset.content.data(),static_cast<std::streamsize>(asset.content.size()));
            }
        } catch (const fs::filesystem_error& e) {fs::remove_all(tempRoot);reportError(std::string("ERROR: Could not extract web files: ") + e.what());return 1;}
    } if (DEBUGMODE) {cout << "[DEBUG] Website Path: " << webRoot << "\n";}





    /* =========== PHP MANAGEMENT ========== */
    if (phpPath == "") {phpPath = "php";}
    if (HOST == "") {HOST = "0.0.0.0";}

    int phpStatus = std::system((phpPath + " --version >" + nullDevice + " 2>&1").c_str());
    if (DEBUGMODE) {cout << "[DEBUG] PHP Status Check: " + phpPath + " --version >" + nullDevice + " 2>&1\n";}
    if (phpStatus != 0) {reportError("ERROR: Could not access PHP (is it installed and in PATH?).\nTo use a custom PHP path, use --custom-php <PATH>.");return 1;}

    // php -S 0.0.0.0:1234 -t /tmp/.../web/ /tmp/.../web/router.php
    cout << "Starting server on " + HOST + ":" << PORT << "...\n";
    str phpCommand = phpPath + " -S " + HOST + ":" + std::to_string(PORT) + " -t " + webRoot.string() + " " + (webRoot / "router.php").string();
    if (DEBUGMODE) {cout << "[DEBUG] PHP Command: " + phpCommand + "\n";}

    cout << "\n";
    int serverStatus = std::system(phpCommand.c_str());
    if (webPath == "") {fs::remove_all(tempRoot);}
    return serverStatus;
}