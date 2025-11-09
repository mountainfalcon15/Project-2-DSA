#include <iostream>
#include <string>
#include "rapidjson/include/rapidjson/document.h"
#include <fstream>
#include <set>
#include <vector>
#include <regex>
#include "Game.h"
#include "Minheap.h"
#include "Btree.h"

using namespace std;
using namespace rapidjson;

int main(int argc, char* argv[]) {
    // Data Parsing
    ifstream file("C:/Users/mount/CLionProjects/games.json");
    if (!file.is_open()) {
        cout << "Failed to open file (dies)" << endl;
        return 1;
    }

    // Converts json file into DOM tree where data is automatically converted into proper form
    cout << "Converting to DOM tree..." << endl;
    string json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    Document data;
    data.Parse(json.c_str());

    cout << "Waiting for values to be added..." << endl;

    // Data structures that will be used
    Minheap MH;
    Btree BT(3);
    vector<string> GameGenre;
    set<string> genres;
    vector<int> IDS;
    map<string, Game> GameSearch;

    int incrementer = 0;

    // Goes through Document object and its members
    // Create Game objects from the data
    for (auto& member : data.GetObject()) {
        cout << "processing game " << incrementer << endl;
        string id = member.name.GetString();
        const auto& obj = member.value;
        string name = obj["name"].GetString();
        float price = obj["price"].GetFloat();
        string description = obj["short_description"].GetString();
        // Append genres to Set
        for (int i=0 ; i < obj["genres"].Size(); i++) {
            GameGenre.push_back(obj["genres"][i].GetString());
            genres.insert(obj["genres"][i].GetString());
        }

        //calculate review score: #pos/total reviews
        float score = 0;
        int pos = obj["positive"].GetInt();
        int neg = obj["negative"].GetInt();
        if(pos+neg != 0) score = float(pos)/(float(pos)+float(neg));
        //cout << "positive scores: " << pos << ", negative scores: " << neg << ";    computed score: " << score << endl;
        Game game = Game(id, name, price, description, GameGenre, score, pos, neg);
        // Append Game to our data structures
        // Minheap and btree will sort the data
        GameSearch[id] = game;
        //MH.insert(game);
        //BT.insert(game);
        if (incrementer > 2000) {
            break;
        }
        incrementer++;
    }

    // Program loop
    string input;
    while(true) {
        cout << "------------------------------" << endl;
        cout
                << "Welcome to the Steamler! This is a program that helps you pick out games for you based on the genre(s) you select!"
                << std::endl;
        cout << "1. See all genres" << endl;
        cout << "2. Enter genres to search" << endl;
        cout << "3. Exit" << endl;
        cout << "------------------------------" << endl;
        cout << "Please enter a number to begin: ";
        cin >> input;
        if (input == "1") {
            for (auto genre: genres) {
                cout << genre << ", ";
            }
            cout << endl;
        }
        if (input == "2") {
            cout << "Separate genres using commas (ie. Action, Single-Player)" << endl;
            cout << "Enter genres here: " << endl;

            //get genres specified
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, input);
            vector<string> genres;
            string temp = "";

            //parse thru genre input
            for (char c: input) {
                if (c == ',') {
                    if (!temp.empty()) {
                        if(temp[0] == ' ') temp = temp.substr(1);
                        genres.push_back(temp);
                    }
                    temp.clear();
                } else temp += c;

            }
            if (!temp.empty()) {
                if(temp[0] == ' ') temp = temp.substr(1);
                genres.push_back(temp);
            }

            // IMPLEMENT SORTS/ALGOS HERE TO FIND GAMES AND COMPARE TIMES(SHOW RESULTS)
            Minheap minheap;
            for(int ID : IDS){
                int size = 0;
                Game game = GameSearch[to_string(ID)];

                //check for a genre match
                bool match = true;
                vector<string> game_genres = game.getGenres();
                for(string genre : genres){
                    auto it = find(game_genres.begin(),game_genres.end(), genre);
                    if(it == game_genres.end()) match = false;
                }
                if(match = true){
                    minheap.insert(game);
                    size+=1;
                    //control size of minheap
                    if(size > 20){
                        minheap.extractMin();
                    }
                }
            }
            cout << "The top 20 " << input << " games:" << endl;
            minheap.print();
        }
        if (input == "3") {
            return 0;
        }


    }
    return 0;
}