#include <iostream>
#include <vector>
#include "Game.h"
using namespace std;

#ifndef BTREE_H
#define BTREE_H

struct Node
{
    bool leaf;
    vector<Game> keys;
    vector<Node*> children;
    int t;

    Node(bool leaf, int t);
};

class Btree
{
    Node* root;
    int t;

    void splitChild(Node* parent, int i);
    void insertNonFull(Node* node, Game g);

public:
    Btree(int degree);

    void insert(Game g);

    void reverseInorderTraversal(Node* node,vector<Game>& topGames, int limit);
    vector<Game> getTopGames(int n);

};


#endif //BTREE_H
