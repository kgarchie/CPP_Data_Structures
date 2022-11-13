#include <iostream>
//// PQHeap.cpp
//// Implement your Heap Priority Queue in this file
#include "PriorityQueue.h"

// Your code here

#include <string>
#include <memory>

namespace std{
    template<class T> struct _Unique_if {
        typedef unique_ptr<T> _Single_object;
    };

    template<class T> struct _Unique_if<T[]> {
        typedef unique_ptr<T[]> _Unknown_bound;
    };

    template<class T, size_t N> struct _Unique_if<T[N]> {
        typedef void _Known_bound;
    };

    template<class T, class... Args>
    typename _Unique_if<T>::_Single_object
    make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<class T>
    typename _Unique_if<T>::_Unknown_bound
    make_unique(size_t n) {
        typedef typename remove_extent<T>::type U;
        return unique_ptr<T>(new U[n]());
    }

    template<class T, class... Args>
    typename _Unique_if<T>::_Known_bound
    make_unique(Args&&...) = delete;
}

// Constructors
PriorityQueue::PriorityQueue() {
    max_capacity = DEFAULT_MAX_CAPACITY;
    pq = std::make_unique<Element[]>(max_capacity);
}

PriorityQueue::PriorityQueue(int size) {
    max_capacity = size;
    pq = std::make_unique<Element[]>(max_capacity);
}

// Inserts a new object into the priority queue. Returns true if the insertion is successful. If the PQ is full, the insertion is aborted, and the method returns false.
bool PriorityQueue::insert(Element &element) {
    if (isFull()) {
        return false;
    } else {
        for (int i = 0; i < max_capacity; i++) {
            if (pq[i].name == "None") {
                pq[i] = element;
                pq[i].fifo = i;
                break;
            }
        }
        return true;
    }
}

// The object of the highest priority must be the one returned by the remove() method; and if multiple objects have the same priority, the one in the queue the longest shall be returned, ie, FIFO return order must be preserved for objects of identical priority. Returns the default constructed Element if the PQ is empty.
Element PriorityQueue::remove() {
    if (isEmpty()) {
        return Element();
    } else {
        Element highest = pq[0];
        for (int i = 0; i < max_capacity; i++) {
            if (pq[i].priority > highest.priority) {
                highest = pq[i];
            } else if (pq[i].priority == highest.priority && pq[i].fifo < highest.fifo) {
                highest = pq[i];
            }
        }
        for (int i = 0; i < max_capacity; i++) {
            if (pq[i].name == highest.name && pq[i].priority == highest.priority && pq[i].fifo == highest.fifo) {
                pq[i].name = "None";
                pq[i].priority = -1;
            }
        }
        return highest;
    }
}

// Deletes all instances of the parameter from the PQ if found, and returns true. Returns false if no match to the parameter obj is found.
bool PriorityQueue::del(Element &element) {
    if (contains(element)) {
        for (int i = 0; i < max_capacity; i++) {
            if (pq[i].name == element.name && pq[i].priority == element.priority) {
                pq[i].name = "None";
                pq[i].priority = -1;
                pq[i].fifo = -1;
            }
        }
        return true;
    } else {
        return false;
    }
}

// Returns the object of highest priority in the PQ; if multiple objects have the same highest priority, return the one that has been in the PQ the longest, but does NOT remove it. Returns default constructed Element if the PQ is empty.

Element PriorityQueue::peek() {
    if (isEmpty()) {
        return Element();
    } else {
        Element highest = pq[0];

        for (int i = 0; i < max_capacity; i++) {
            if (pq[i].priority > highest.priority) {
                highest = pq[i];
            } else if (pq[i].priority == highest.priority && pq[i].fifo < highest.fifo) {
                highest = pq[i];
            }
        }
        return highest;
    }
}

// Returns true if the pq contains the specified element
bool PriorityQueue::contains(Element &element) {
    for (int i = 0; i < max_capacity; i++) {
        if (pq[i].name == element.name && pq[i].priority == element.priority) {
            return true;
        }
    }
    return false;
}

// Returns the number of objects currently in the PQ.
int PriorityQueue::size() {
    int size = 0;
    for (int i = 0; i < max_capacity; i++) {
        if (pq[i].name != "None") {
            size++;
        }
    }
    return size;
}

// Returns the PQ to its default state.
void PriorityQueue::clear() {
    for (int i = 0; i < max_capacity; i++) {
        pq[i].name = "None";
        pq[i].priority = -1;
        pq[i].fifo = -1;
    }
}

// Returns true if the PQ is empty
bool PriorityQueue::isEmpty() {
    for (int i = 0; i < max_capacity; i++) {
        if (pq[i].name != "None") {
            return false;
        }
    }
    return true;
}

// Returns true if the PQ is full
bool PriorityQueue::isFull() {
    for (int i = 0; i < max_capacity; i++) {
        if (pq[i].name == "None") {
            return false;
        }
    }
    return true;
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