#include "Minheap.h"

Minheap::Minheap(){
    minheap = {};
}

void Minheap::insert(Game g){
    //root insert into empty heap
    if(minheap.size() == 0) minheap.push_back(g);
    else{
        //push value into next empty spot in the tree
        minheap.push_back(g);

        //heapify using recursive heapify function, passing index
        heapify(minheap.size()-1);
    }
}

void Minheap::heapify(int index){
    if(index != 0) { //check if heapify has reached root
        //get index of parent
        int parent = (index - 1) / 2;

        //parent > value, swap & heapify again, else do nothing
        if (minheap[index] < minheap[parent]) {
            Game parent_obj = minheap[parent];
            minheap[parent] = minheap[index];
            minheap[index] = parent_obj;

            //repeat heapify with index of parent (aka new index of value after swap)
            heapify(parent);
        }
    }
}

void Minheap::heapify_down(int index){
    //find index of children
    int left_child = 2*index+1;
    int right_child = 2*index+2;

    //case 1: both children exist
    if(minheap.size() - 1 >= right_child){

        //subcase 1: element is larger than children, right is smallest
        if(minheap[index] > minheap[right_child] && minheap[right_child] < minheap[left_child]){
            //swap element and right child
            Game child = minheap[right_child];
            minheap[right_child] = minheap[index];
            minheap[index] = child;

            //recursively call heapify_down with new position of element
            heapify_down(right_child);
        }

        //subcase 2: element is larger than children, left is smallest
        if(minheap[index] > minheap[left_child] && minheap[left_child] < minheap[right_child]){
            //swap element and left child
            Game child = minheap[left_child];
            minheap[left_child] = minheap[index];
            minheap[index] = child;

            //recursively call heapify_down with new position of element
            heapify_down(left_child);
        }

        //subcase 3: element is smaller than children, do nothing
    }

    //case 2: left child exists, no right
    else if(minheap.size() - 1 <= left_child){
        //subcase 1: element is smaller than child
        if(minheap[index] > minheap[left_child]){
            //swap element and left child
            Game child = minheap[left_child];
            minheap[left_child] = minheap[index];
            minheap[index] = child;

            //recursively call heapify_down with new position of element
            heapify_down(left_child);
        }
    }
    //case 3: element has reached bottom of heap. do nothing
}

Game Minheap::extractMin() {
    //save minimum value to return
    Game min = minheap[0];

    //move the last element to the front of the heap
    minheap[0] = minheap[minheap.size()-1];
    //pop the last element, as size has decreased
    minheap.pop_back();
    //recursively heapify down
    heapify_down(0);

    return min;
}

Game Minheap::peek(){
    return minheap[0];
}

void Minheap::print(){
    for(Game game : minheap){
        game.display();
    }
    cout << endl;
}