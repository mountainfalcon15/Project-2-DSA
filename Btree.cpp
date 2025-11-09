#include "Btree.h"

Node::Node(bool leaf, int t){
    this->leaf = leaf;
    this->t = t;
}


Btree::Btree(int degree){
    root = nullptr;
    this->t = degree;
}

void Btree::insert(Game game){
    //empty root
    if(root == nullptr){
        root = new Node(true, t);
        root->keys.push_back(game);
        return;
    }
    //if root is full, update root, split original
    if(root->keys.size() == 2 * t - 1) {
        //create new root, add current root to its children
        Node* s = new Node(false, t);
        s->children.push_back(root);
        //split the original root
        splitChild(s, 0);
        root = s;
    }
    //normal insert
    insertNonFull(root, game);
}

void Btree::splitChild(Node* parent, int i) {
    Node* y = parent->children[i];
    Node* z = new Node(y->leaf, t);

    //move top t-1 keys to j
    for(int j = 0; j < t - 1; j++)
        z->keys.push_back(y->keys[j + t]);

    //move non-leaf children
    if(!y->leaf) {
        for(int j = 0; j < t; j++)
            z->children.push_back(y->children[j + t]);
    }

    // Reduce y keys
    y->keys.resize(t - 1);
    if(!y->leaf)
        y->children.resize(t);

    //insert new child into parent's children list
    parent->children.insert(parent->children.begin() + i + 1, z);

    //insert value into parent's keys
    parent->keys.insert(parent->keys.begin() + i, y->keys[t - 1]);
}

void Btree::insertNonFull(Node* node, Game game) {
    int i = node->keys.size() - 1;

    //check for leaf
    if(node->leaf) {
        node->keys.push_back(game);
        while(i >= 0 && node->keys[i] > game) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = game;
    } else {
        while(i >= 0 && node->keys[i] > game)
            i--;

        i++;

        //check for full node, splits if so
        if(node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i);
            if(game > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], game);
    }
}

//reverse inorder to get highest scores first
void Btree::reverseInorderTraversal(Node* node, vector<Game>& topGames, int limit) {
    if (!node || topGames.size() >= limit)
        return;

    //visit right child first (higher scores)
    for (int i = node->keys.size(); i >= 0; i--) {
        if (!node->leaf) reverseInorderTraversal(node->children[i], topGames, limit);

        if (i > 0 && topGames.size() < limit) {
            topGames.push_back(node->keys[i-1]);
        }
    }
}

vector<Game> Btree::getTopGames(int n = 20) {
    vector<Game> topGames;
    reverseInorderTraversal(root, topGames, n);
    return topGames;
}

