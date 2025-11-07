#include <iostream>
#include <string>
#include "rapidjson/include/rapidjson/document.h"
#include <fstream>
#include <set>
#include <vector>
#include <regex>
#include "Game.h"
#include "Minheap.h"

using namespace std;
using namespace rapidjson;

int main(int argc, char* argv[]) {
    // Data Parsing
    ifstream file("C:/Users/macy7/CLionProjects/DSA Project 2/Project-2-DSA/games.json");
    if (!file.is_open()) {
        cout << "dies" << endl;
        return 1;
    }
    // Converts json file into DOM tree where data is automatically converted into proper form
    cout<< "test";
    string json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    Document data;
    data.Parse(json.c_str());

    cout << data.MemberCount();

    // Data structures that will be used
    Minheap MH;
    //Btree BT;
    vector<string> GameGenre;
    set<string> genres;
    map<string, Game>;

    // Goes through Document object and its members
    // Create Game objects from the data
    for (auto& obj : data.GetArray()) {
        //string id = obj["id"].GetString();
        string name = obj["name"].GetString();
        float price = obj["price"].GetFloat();
        string description = obj["detailed_description"].GetString();
        //array genres = obj["genres"].GetArray();
        for (int i=0 ; i < obj["genres"].Size(); i++) {
            GameGenre.push_back(obj["genres"][i].GetString());
            genres.insert(obj["genres"][i].GetString());
        }
        Game game = Game("test", name, price, description, GameGenre);
        // Append Game to data structures(sorted by game id)

        //MH.insert(game);
        //BT.insert(game);
        break;
    }

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
            for (auto genre: genres) {
                cout << genre << ", " ;
            }
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