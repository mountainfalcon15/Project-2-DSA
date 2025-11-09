#include "Btree.h"

Node::Node(bool leaf, int t){
    this->leaf = leaf;
    this->t = t;
}


Btree::Btree(int degree){
    root = nullptr;
    this->t = degree;
}

void Btree::insert(int val){
    //empty root
    if(root == nullptr){
        root = new Node(true, t);
        root->keys.push_back(val);
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
    insertNonFull(root, val);
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

void Btree::insertNonFull(Node* node, int key) {
    int i = node->keys.size() - 1;

    //check for leaf
    if(node->leaf) {
        node->keys.push_back(key);
        while(i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
    } else {
        while(i >= 0 && node->keys[i] > key)
            i--;

        i++;

        //check for full node, splits if so
        if(node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i);
            if(key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

bool Btree::search(int key) {
    //current node tracker
    Node* cur = root;
    while(cur) {
        int i = 0;
        //iterate through a node's keys
        while(i < cur->keys.size() && key > cur->keys[i]) i++;
        //if key matches value, returns true
        if(i < cur->keys.size() && cur->keys[i] == key)
            return true;
        //if reaches end of tree, returns false
        if(cur->leaf) return false;
        //sets value to child
        cur = cur->children[i];
    }
    return false;
}

void Btree::inorderTraversal(Node* node) {
    //empty check
    if(!node) return;

    for(size_t i = 0; i < node->keys.size(); i++) {
        if(!node->leaf) inorderTraversal(node->children[i]);
        std::cout << node->keys[i] << " ";
    }
    if(!node->leaf) inorderTraversal(node->children[node->keys.size()]);
}

void Btree::printSorted() {
    inorderTraversal(root);
    std::cout << "\n";
}
