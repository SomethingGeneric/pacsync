#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>

#include <stdlib.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace fs = std::filesystem;

using namespace std;

// Stuff that can be edited 
string tgt_missing = "You didn't include a target! :(\n";
string home = getenv("HOME");
string user = getenv("USER");

string config_dir = home + "/.config/aurtomatic/";
string config_fn = "settings.conf";

// Stuff loaded from config
string out_dir = "";
string data_dir = "";
string repo_name = "";

bool proc(const string command) {
    int code = system(command.c_str());
    printf("Exit code: %i\n", code);
    if (code == 0) {
        return true;
    } else {
        return false;
    }
}

bool loadconfig() {

    if (fs::is_directory(config_dir) && fs::is_regular_file(config_dir + config_fn)) {
        // pain
        cout << "Loading config from " << config_dir << "\n";
    } else {
        cout << "Seems like we haven't configured things yet.\n";
        
        // guess cpp fs standard is still WIP
        // does this still work if the dir exists? guess so
        mkdir(config_dir.c_str(), 0777);
        
        cout << "Directory to hold package folders (full path): ";
        cin >> data_dir;
        
        cout << "Directory to hold repo (full path): ";
        cin >> out_dir;

        cout << "Repo name: ";
        cin >> repo_name;

        ofstream config;
        config.open(config_dir + config_fn);
        config << "datadir=" << data_dir << "\n";
        config << "outdir=" << out_dir << "\n";
        config << "repo_name" << repo_name << "\n";
        config.close();

        cout << "Here are your configured settings\n";
        cout << "Package storage: " << data_dir << "\n";
        cout << "Output repo: " << out_dir << "\n";
        cout << "Repo name: " << repo_name << "\n";


    }

    return true;
}

bool add(const string target) {
    return true;
}

bool remove(const string target) {
    return true;
}

bool update() {
    return true;
}

int main(int argc, char *argv[]) {

    bool conf = loadconfig();

    if (argc == 1) {
        cout << "You need to give me instructions. See 'help'\n";
    } else {
        string command = argv[1];
        if (command == "add") {
            if (argc != 3) {
                cout << tgt_missing;
            } else { // this is probably even lazier than I realize
                string target = argv[2];
                bool res = add(target);
                if (res) {
                    return 0;
                } else {
                    return 1;
                }
            }
        } else if (command == "remove") {
            if (argc != 3) {
                cout << tgt_missing;
            } else { // this is probably even lazier than I realize
                string target = argv[2];
                bool res = remove(target);
                if (res) {
                    return 0;
                } else {
                    return 1;
                }
            }
        } else if (command == "update") {
            cout << "Todo\n";
        } else {
            // TODO: show some kind of help
            cout << "I'll write usage docs once I have a functional program.\n";
        }
    }
    return 0;
}