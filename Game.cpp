//
// Created by macy7 on 10/28/2025.
//

#include "Game.h"

Game::Game() {
    this-> name = "";
    this-> price = 0.00;
    this-> description = "";
    this->genres = vector<string>{};
    this->score = 0;
}

Game::Game(string id, string name, vector<string> genres, float score) {
    this-> id = id;
    this-> name = name;
    this-> genres = genres;
    this-> score = score;
}

Game::Game(string id, string name, float price, string description, vector<string> genres) {
    this-> id = id;
    this->name = name;
    this->price = price;
    this->description = description;
    this->genres = genres;
}

Game::Game(string id, string name, float price, string description, vector<string> genres, float score, int pos, int neg) {
    this-> id = id;
    this->name = name;
    this->price = price;
    this->description = description;
    this->genres = genres;
    this->score = score;
    this->pos = pos;
    this->neg = neg;
}

bool Game::operator<(const Game& other) const {
    return this->score < other.getScore();
}
bool Game::operator>(const Game& other) const {
    return this->score > other.getScore();
}
bool Game::operator==(const Game& other) const {
    return this->score == other.getScore();
}

string Game::getName() {
    return name;
}

float Game::getPrice() {
    return price;
}

string Game::getId() {
    return id;
}

string Game::getDescription() {
    return description;
}

vector<string> Game::getGenres() {
    return genres;
}

float Game::getScore() const{
    return score;
}

void Game::display(){
    cout << "Name: " << name << endl;
    cout << "Price: " << price << endl;
    cout << "Description: " << description << endl;
    cout << "Review Score: " << score*100 << " from " << pos << " positive and " << neg << " negative reviews." << endl;
}
