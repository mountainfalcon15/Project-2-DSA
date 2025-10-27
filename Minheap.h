#include <iostream>
#include <vector>
using namespace std;

#ifndef MINHEAP_H
#define MINHEAP_H

class Minheap
{
vector<int> minheap;
void heapify(int index);
void heapify_down(int index);

public:
Minheap();

void insert(int val);
int extractMin();

void print();
};

#endif //MINHEAP_H
