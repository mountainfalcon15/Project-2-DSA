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
    int smallest = index;

    if(left_child < minheap.size() && minheap[left_child] < minheap[smallest])
        smallest = left_child;
    if(right_child < minheap.size() && minheap[right_child] < minheap[smallest])
        smallest = right_child;

    if(smallest != index){
        //swap element and left child
        Game child = minheap[smallest];
        minheap[smallest] = minheap[index];
        minheap[index] = child;
        heapify_down(smallest);
    }
}

Game Minheap::extractMin() {
    if(minheap.empty()) throw runtime_error("Heap is empty");
    //save minimum value to return
    Game min = minheap[0];

    //move the last element to the front of the heap
    minheap[0] = minheap[minheap.size()-1];
    //pop the last element, as size has decreased
    minheap.pop_back();
    //recursively heapify down
    if(!minheap.empty()) heapify_down(0);

    return min;
}

Game Minheap::peek(){
    if(minheap.size()!= 0) return minheap[0];
    else throw runtime_error("empty heap");
}

void Minheap::print(){
    for(Game game : minheap){
        game.display();
        cout << endl;
    }
}