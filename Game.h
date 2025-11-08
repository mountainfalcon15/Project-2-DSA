//
// Created by macy7 on 10/28/2025.
//

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
using namespace std;

class Game {
    string id;
    string name;
    float price;
    string description;
    vector<string> genres;

public:
    Game();
    Game(string id, string name, vector<string> genres);
    Game(string id, string name, float price, string description, vector<string> genres);
    string getName();
    float getPrice();
    string getId();
    string getDescription();
    vector<string> getGenres();

};



#endif //GAME_H
