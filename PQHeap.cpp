//// PQHeap.cpp
//// Implement your Heap Priority Queue in this file
#include "PriorityQueue.h"
#include "TestDriver.h"
// Your code here

#include <iostream>


// Constructor
PriorityQueue::PriorityQueue() {
    max_capacity = DEFAULT_MAX_CAPACITY;
    pq = std::make_unique<Element[]>(DEFAULT_MAX_CAPACITY);
}

// Parameterized constructor
PriorityQueue::PriorityQueue(int size) {
    max_capacity = size;
    pq = std::make_unique<Element[]>(size);
}

bool PriorityQueue::insert(Element &element) {
    if (size() == max_capacity) {
        return false;
    }

    if (size() == 0) {
        pq[0] = element;
        return true;
    }

    // find correct insertion point
    int insertIndex = 0;
    // compare priorities
    if (pq[0].priority < element.priority) {

    } else if (pq[0].priority > element.priority) {

    } else {
        // compare fifo
        if (pq[0].fifo < element.fifo) {

        } else if (pq[0].fifo > element.fifo) {

        }
    }
    // insert element
    pq[insertIndex] = element;
    return true;
}

Element PriorityQueue::remove() {
    if (isEmpty()) {
        Element element;
        return element;
    }

    Element element = pq[0];
    // shift all other cells down by one
    for (int i = 0; i < size(); i++) {
        pq[i] = pq[i + 1];
    }

    return element;
}

bool PriorityQueue::del(Element &element) {
    if (isEmpty()) {
        return false;
    }

    bool isFound = false;
    // find index of element to delete
    int i = 0;
    for (; i < size(); i++) {
        if (pq[i].name == element.name) {
            isFound = true;
            break;
        }
    }

    // if element is not found, return false
    if (!isFound) {
        return false;
    }

    // shift all other cells down by one
    for (int j = i; j < size(); j++) {
        pq[j] = pq[j + 1];
    }

    return true;
}

Element PriorityQueue::peek() {
    if (isEmpty()) {
        Element element;
        return element;
    }

    return pq[0];
}

bool PriorityQueue::contains(Element &element) {
    for (int i = 0; i < size(); i++) {
        if (pq[i].name == element.name) {
            return true;
        }
    }
    return false;
}

int PriorityQueue::size() {
    // iterate through all elements
    int count = 0;
    for (int i = 0; i < max_capacity; i++) {
        if (pq[i].name != "None") {
            count++;
        }
    }
    return count;
}

void PriorityQueue::clear() {
    for (int i = 0; i < max_capacity; i++) {
        pq[i].name = "None";
        pq[i].priority = -1;
    }
}

bool PriorityQueue::isEmpty() {
    return size() == 0;
}

bool PriorityQueue::isFull() {
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
   test_PQHeap();
   return 0;
}


/*
Uncomment the below code to quickly test
*/

// int main() {

//     PriorityQueue pq(7);

//     Element element1("Tom", 3);
//     Element element2("John", 5);
//     Element element3("Mike", 4);
//     Element element4("Chris", 1);
//     Element element5("Peter", 2);

//     pq.insert(element1);
//     pq.insert(element2);
//     pq.insert(element3);
//     pq.insert(element4);
//     pq.insert(element5);

//     pq.remove();

//     std::cout << element1.name << ": " << element1.priority << std::endl;
//     std::cout << element2.name << ": " << element2.priority << std::endl;
//     std::cout << element3.name << ": " << element3.priority << std::endl;
//     std::cout << element4.name << ": " << element4.priority << std::endl;
//     std::cout << element5.name << ": " << element5.priority << std::endl;
//     return 0;
// }