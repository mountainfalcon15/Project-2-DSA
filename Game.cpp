//
// Created by macy7 on 10/28/2025.
//

#include "Game.h"

Game::Game() {
    this-> name = "";
    this-> price = 0.00;
    this-> description = "";
    this->genres = vector<string>{};
}

Game::Game(string id, string name, vector<string> genres) {
    this-> id = id;
    this-> name = name;
    this-> genres = genres;
}

Game::Game(string id, string name, float price, string description, vector<string> genres) {
    this-> id = id;
    this->name = name;
    this->price = price;
    this->description = description;
    this->genres = genres;
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
