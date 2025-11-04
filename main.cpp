#include <iostream>
#include <string>
#include "rapidjson/include/rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;
using namespace rapidjson;

int main(int argc, char* argv[]) {
    // Data Parsing
    ifstream file("C:/Users/macy7/CLionProjects/DSA Project 2/Project-2-DSA/games.json");
    if (!file.is_open()) {
        cerr << "Cannot open games.json" << endl;
        return 1;
    }
    cout<< "test";
    string json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    Document data;
    data.Parse(json.c_str());

    cout << data.MemberCount();

    // for (auto& obj : data.GetArray()) {
    //
    // }

    // Program loop
    cout<< "hi";
    string input;
    while(true) {
        cout << "------------------------------" << std::endl;
        cout << "Welcome to the Steamler! This is a program that helps you pick out games for you based on the genre(s) you select!" << std::endl;
        cout << "1. See all genres based on popularity" << std::endl;
        cout << "2. Enter genres to search" << std::endl;
        cout << "3. Exit" << std::endl;
        cout << "------------------------------" << std::endl;
        cout << "Please enter a number to begin: " ;
        cin >> input;
        if (input == "1") {

        }
        if (input == "2") {
            std::cout << "Separate genres using commas (ie. Action, Single-Player)" << std::endl;

        }
        if (input == "3") {
            return 0;
        }
    }
    return 0;
}