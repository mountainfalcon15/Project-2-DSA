//
// Created by macy7 on 10/28/2025.
//

#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Game {
    string id;
    string name;
    float price;
    string description;
    vector<string> genres;
    float score;
    int pos;
    int neg;

public:
    Game();
    Game(string id, string name, vector<string> genres, float score);
    Game(string id, string name, float price, string description, vector<string> genres);
    Game(string id, string name, float price, string description, vector<string> genres, float score, int pos, int neg);
    bool operator<(const Game& other) const;
    bool operator>(const Game& other) const;
    bool operator==(const Game& other) const;
    string getName();
    float getPrice();
    string getId();
    string getDescription();
    float getScore() const;
    int getReviewNum();
    vector<string> getGenres();
    void display();

};



#endif //GAME_H
