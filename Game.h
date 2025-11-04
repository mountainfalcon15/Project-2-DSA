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
    Game(string id, string name, float price, string description, vector<string> genres);

};



#endif //GAME_H
