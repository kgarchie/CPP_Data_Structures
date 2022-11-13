// PQLinkedList.cpp
// Implement your Linked List Priority Queue in this file.
#include "PriorityQueue.h"
#include "TestDriver.h"
// Your code here
// Note: For linked list do NOT use std::unique_ptr<Element[]> pq;
// You must create your own node struct in this file.

// PQLinkedList.cpp
// This file implements functions declared in PriorityQueue.h

#include <iostream>
#include <string>
#include <utility>
#include <memory>

using namespace std;

// Default constructor
PriorityQueue::PriorityQueue()
{
    this->max_capacity = DEFAULT_MAX_CAPACITY;
    this->pq = make_unique<Element[]>(max_capacity);
}

// Parameterized constructor
PriorityQueue::PriorityQueue(int size)
{
    this->max_capacity = size;
    this->pq = make_unique<Element[]>(max_capacity);
}

// This function inserts a new element into the priority queue while maintaining the order of the priority queue
bool PriorityQueue::insert(Element &element)
{
    bool success=false;
    int index = 0;
    Element temp;
    if(!isFull()){
        while(index<size() && pq[index].priority>=element.priority){
            index++;
        }
        for(int i = size(); i > index; i--) {
            pq[i] = pq[i-1];
        }
        pq[index] = element;
        success = true;
    }
    else{
        cout<<"PriorityQueue is full"<<endl;
    }
    return success;
}

// This function removes the highest priority element from the priority queue
Element PriorityQueue::remove()
{
    Element element;
    if(!isEmpty()){
        element.name = pq[0].name;
        element.priority = pq[0].priority;
        element.fifo = pq[0].fifo;
        for(int i=0; i<size()-1; i++){
            pq[i] = pq[i+1];
        }
        pq[size()-1].name = "None";
        pq[size()-1].priority = -1;
        pq[size()-1].fifo = 0;
    }
    else{
        cout<<"PriorityQueue is empty"<<endl;
    }
    return element;
}

// This function deletes the first instance of the element from the priority queue
bool PriorityQueue::del(Element &element)
{
    bool success = false;
    if(!isEmpty()){
        for(int i=0; i<size(); i++){
            if(pq[i].name == element.name && pq[i].priority == element.priority && pq[i].fifo == element.fifo){
                success = true;
                for(int j=i; j<size()-1; j++){
                    pq[j] = pq[j+1];
                }
                pq[size()-1].name = "None";
                pq[size()-1].priority = -1;
                pq[size()-1].fifo = 0;
                break;
            }
        }
    }
    else{
        cout<<"PriorityQueue is empty"<<endl;
    }
    return success;
}

// This function returns the highest priority element from the priority queue without removing the element
Element PriorityQueue::peek()
{
    Element element;
    if(!isEmpty()){
        element.name = pq[0].name;
        element.priority = pq[0].priority;
        element.fifo = pq[0].fifo;
    }
    else{
        cout<<"PriorityQueue is empty"<<endl;
    }
    return element;
}

// This function returns true if the priority queue contains the specified element
bool PriorityQueue::contains(Element &element)
{
    bool success = false;
    if(!isEmpty()){
        for(int i=0; i<size(); i++){
            if(pq[i].name == element.name && pq[i].priority == element.priority && pq[i].fifo == element.fifo){
                success = true;
            }
        }
    }
    else{
        cout<<"PriorityQueue is empty"<<endl;
    }
    return success;
}

// This function returns the current size of the priority queue
int PriorityQueue::size()
{
    int count = 0;
    if(!isEmpty()){
        for(int i=0; i<max_capacity; i++){
            if(pq[i].priority != -1){
                count++;
            }
        }
    }
    return count;
}

// This function clears the priority queue
void PriorityQueue::clear()
{
    if(!isEmpty()){
        for(int i=0; i<size(); i++){
            pq[i].name = "None";
            pq[i].priority = -1;
            pq[i].fifo = 0;
        }
    }
}

// This function returns true if the priority queue is empty
bool PriorityQueue::isEmpty()
{
    return size() == 0;
}

// This function returns true if the priority queue is full
bool PriorityQueue::isFull()
{
    return size() == max_capacity;
}


/* IMPORTANT: main() must be EXACTLY how it was provided
** provided to you when you submit your assignment.
**
** If you edit main for your own testing purposes,
** you MUST restore it to how it was provided to
** you before submission.
*/
int main() {
   test_PQLinkedList();
   return 0;
}


