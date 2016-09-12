//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
    // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
    // no clean-up to do, since the heap is not dynamically allocated
}

void HeapPriorityQueue::put_in(PuzzleState *elem) {
    // TODO:  Put your code here!
    //use vector functions to add elem to back of heap define its index
    heap.push_back(elem);
    int index = (int)heap.size() - 1;
    int parentIndex = parent(index);
    //order the heap after insert
    while(heap[parentIndex]->getBadness() > heap[index]->getBadness() && !is_root(index)){
        PuzzleState* temp = heap[parentIndex];
        heap[parentIndex] = heap[index];
        heap[index] = temp;
        index = parentIndex;
        parentIndex = parent(index);
    }
}

PuzzleState * HeapPriorityQueue::take_out() {
    assert(!is_empty());
    
    // TODO:  Put your code here!
    int index, target;
    PuzzleState* returnVal = heap[0];
    index = 0;
    PuzzleState* temp = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap[heap.size() -1] = temp;
    heap.pop_back();  //delete last element of heap
    
    while(true){
        target = index;
        //to prevent segmentation fault
        if (first_child(target) >= heap.size()) {break;}
        if (first_child(target) + 1 < heap.size()){
            int left_badness = heap[first_child(target)]->getBadness();
            int right_badness = heap[first_child(target) + 1]->getBadness();
            // which child has lower badness, left or right
            if (left_badness >= right_badness){
                    target = first_child(target) + 1;
                }
            else target = first_child(target);
        }
        else target = first_child(target);
        
        //swapDown to bring target to right position by comparing badness
        if ((heap[index]->getBadness() >= heap[target]->getBadness())){
                PuzzleState* temp = heap[target];
                heap[target] = heap[index];
                heap[index] = temp;
                index = target;
            }
        else break;
       	
    }
    return returnVal;
    
}


bool HeapPriorityQueue::is_empty() {
    return (heap.size() == 0);
}

int HeapPriorityQueue::parent(int index) {
    return (index - 1) / 2;
}

int HeapPriorityQueue::first_child(int index) {
    return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
    return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
    return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
    int fchild = first_child(index);
    return max(0, min(2, (int)heap.size() - fchild));
}

#endif