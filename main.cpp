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
    string json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    Document data;
    data.Parse(json.c_str());

    cout << "Waiting for values to be added..." << endl;

    // Data structures that will be used
    Minheap MH;
    //Btree BT;
    vector<string> GameGenre;
    set<string> genres;
    vector<int> IDS;
    map<string, Game> GameSearch;

    int incrementer;

    // Goes through Document object and its members
    // Create Game objects from the data
    for (auto& member : data.GetObject()) {
        string id = member.name.GetString();
        const auto& obj = member.value;
        string name = obj["name"].GetString();
        //float price = obj["price"].GetFloat();
        //string description = obj["short_description"].GetString();
        // Append genres to Set
        for (int i=0 ; i < obj["genres"].Size(); i++) {
            GameGenre.push_back(obj["genres"][i].GetString());
            genres.insert(obj["genres"][i].GetString());
        }
        //Game game = Game(id, name, price, description, GameGenre);
        Game game = Game(id, name,GameGenre);
        // Append Game to our data structures
        // Minheap and btree will sort the data
        //GameSearch[id] = game;
        //MH.insert(game);
        //BT.insert(game);
        if (incrementer > 500) {
            break;
        }
        incrementer++;
    }

    // Program loop
    string input;
    while(true) {
        cout << "------------------------------" << endl;
        cout << "Welcome to the Steamler! This is a program that helps you pick out games for you based on the genre(s) you select!" << std::endl;
        cout << "1. See all genres" << endl;
        cout << "2. Enter genres to search" << endl;
        cout << "3. Exit" << endl;
        cout << "------------------------------" << endl;
        cout << "Please enter a number to begin: " ;
        cin >> input;
        if (input == "1") {
            for (auto genre: genres) {
                cout << genre << ", " ;
            }
            cout<< endl;
        }
        if (input == "2") {
            cout << "Separate genres using commas (ie. Action, Single-Player)" << endl;
            cout << "Enter genres here: " << endl;
            cin >> input;
            // IMPLEMENT SORTS/ALGOS HERE TO FIND GAMES AND COMPARE TIMES(SHOW RESULTS)
            //

            cout << "matches found: "  << IDS.size() << endl;
            for (int i = 0; i < IDS.size(); i++) {
                Game display = GameSearch[to_string(IDS[i])];
                cout << "Name: " << display.getName() << endl;
                cout << "Price: " << display.getPrice() << endl;
                cout << "Description: " << display.getDescription() << endl;
            }
        }
        if (input == "3") {
            return 0;
        }
    }
    return 0;
}