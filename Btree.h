#include <iostream>
#include <vector>
using namespace std;

#ifndef BTREE_H
#define BTREE_H

struct Node
{
    bool leaf;
    vector<int> keys;
    vector<Node*> children;
    int t;

    Node(bool leaf, int t);
};

class Btree
{
    Node* root;
    int t;

    void splitChild(Node* parent, int i);
    void insertNonFull(Node* node, int key);

public:
    Btree(int degree);

    void insert(int val);
    bool search(int key);

    void inorderTraversal(Node* node);
    void printSorted();

};


#endif //BTREE_H
