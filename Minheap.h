#include <iostream>
#include <vector>
#include "Game.h"
using namespace std;

#ifndef MINHEAP_H
#define MINHEAP_H

class Minheap
{
vector<Game> minheap;
void heapify(int index);
void heapify_down(int index);

public:
Minheap();

void insert(Game g);
Game extractMin();
Game peek();

void print();
};

#endif //MINHEAP_H
