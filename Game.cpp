//
// Created by macy7 on 10/28/2025.
//

#include "Game.h"

Game::Game(string id, string name, float price, string description, vector<string> genres) {
    this-> id = id;
    this->name = name;
    this->price = price;
    this->description = description;
    this->genres = genres;
}