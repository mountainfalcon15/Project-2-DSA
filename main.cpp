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
    set<string> genres;
    vector<string> IDS;
    map<string, Game> GameSearch;

    int incrementer = 0;

    // Goes through Document object and its members
    // Create Game objects from the data
    for (auto& member : data.GetObject()) {
        cout << "processing game " << incrementer << endl;
        string id = member.name.GetString();
        IDS.push_back(id);
        const auto& obj = member.value;
        string name = obj["name"].GetString();
        float price = obj["price"].GetFloat();
        string description = obj["short_description"].GetString();
        // Append genres to Set
        vector<string> GameGenre;
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
        cout << "2. Enter genres to search via MinHeap" << endl;
        cout << "3. Enter genres to search via BTree" << endl;
        cout << "4. Exit" << endl;
        cout << "------------------------------" << endl;
        cout << "Please enter a number to begin: ";
        cin >> input;
        if (input == "1") {
            for (auto genre: genres) {
                cout << genre << ", ";
            }
            cout << endl;
        }
        if (input == "2" || input == "3") {
            string dataset = input; //saving input
            cout << "Separate genres using commas (ie. Action, Single-Player), case sensitive" << endl;
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
            Btree btree(3);
            int size = 0;
            for(string ID : IDS){
                Game game = GameSearch[ID];

                //check for a genre match
                bool match = true;
                vector<string> game_genres = game.getGenres();
                for(string genre : genres){
                    auto it = find(game_genres.begin(),game_genres.end(), genre);
                    if(it == game_genres.end()){
                        match = false;
                        break;
                    }
                }
                if(match == true && game.getReviewNum() > 100){ //cutoff to ensure games with few pos & 0 negative don't clog results
                    if(dataset == "2") {
                        minheap.insert(game);
                        size +=1;
                    }
                    else btree.insert(game);
                    //control size of minheap
                    if(size > 20){
                        minheap.extractMin();
                    }
                }
            }
            cout << "Top games in categories: " << endl;
            for(int i = 0; i < genres.size() - 1; i++){
                cout << genres[i] << ", ";
            } cout << genres[genres.size()-1] << endl;
            if(dataset == "2") minheap.print();
            else {
                vector<Game> top = btree.getTopGames(20);
                for(auto& g : top){
                    g.display();
                    cout << endl;
                }
            }
        }
        if (input == "4"){
            return 0;
        }


    }
    return 0;
}