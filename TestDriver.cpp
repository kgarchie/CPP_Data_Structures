/** TestDriver.cpp
 * This file contains all of the functions used for testing the PriorityQueue.
 *
 * IMPORTANT: DO NOT EDIT THIS FILE MY COPY WILL BE USED FOR TESTING
 **/

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

// Size used when testing parameterized constructor
#define CONSTRUCTOR_TEST_SIZE 200

// Values to be inserted for testing
const std::string strings[10] = {"Item1", "Item2", "Item3", "Item4", "Item5", "Item6",
                                 "Item7", "Item8", "Item9", "Item10"};
const int priorities[10] = {0, 1, 2, 3, 2, 1, 0, 6, 1, 5};

// Answers for sorted and linked list insert
const std::string answer[10] = {"Item1", "Item7", "Item2", "Item6", "Item9",
                                "Item3", "Item5", "Item4", "Item10", "Item8"};
const int answer_priorities[10] = {0, 0, 1, 1, 1, 2, 2, 3, 5, 6};

// Returns true if two Elements have the same name and priority
bool compare_elements(Element &e1, Element &e2) {
    if (e1.name == e2.name && e1.priority == e2.priority) {
        return true;
    } else {
        return false;
    }
}

// Returns true if two Elements have the same priority
bool compare_priority(Element &e1, Element &e2) {
    if (e1.priority == e2.priority) {
        return true;
    } else {
        return false;
    }
}

// Tests PriorityQueue default constructor and parameterized constructor
// Default constructor expected initialization size of DEFAULT_MAX_CAPACITY
// Parameterized constructor expected correct initialization of given capacity
template<class T>
void test_constructors() {
    try {
        // Default constructor
        std::cout << "---------- Testing: Default Constructor ----------" << std::endl;
        T test1;
        if (test1.max_capacity != DEFAULT_MAX_CAPACITY) {
            std::cout << "Expected size: 1000" << std::endl;
            std::cout << "Returned: " << test1.max_capacity << std::endl;
            throw std::runtime_error("ERROR -> Default constructor not default capacity");
        }
        std::cout << "<TEST PASSED>" << std::endl;

        // Parameterized constructor
        std::cout << "------- Testing: Parameterized Constructor -------" << std::endl;
        T test2(CONSTRUCTOR_TEST_SIZE);
        if (test2.max_capacity != CONSTRUCTOR_TEST_SIZE) {
            throw std::runtime_error("ERROR -> Parameterized constructor does not allocate correct size");
        }
        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void test_insert_heap(PriorityQueue &p) {
    try {
        std::cout << "-------- TESTING: bool insert(Element &e) --------" << std::endl;
        // Array and vector to store the state of pq
        std::string received_names[10];
        std::vector<int> received_priorities;

        // Inserting Elements
        for (int i = 0; i < 10; i++) {
            Element e1;
            e1.name = strings[i];
            e1.priority = priorities[i];
            p.insert(e1);
        }

        std::cout << "Expecting Min-Heap" << std::endl;

        std::cout << "Received: ";
        for (int i = 0; i < 10; i++) {
            received_names[i] = p.pq[i].name;
            received_priorities.push_back(p.pq[i].priority);
            std::cout << " " << p.pq[i].name << ":" << p.pq[i].priority;
        }
        std::cout << "\n";

        if (!std::is_heap(received_priorities.begin(), received_priorities.end(), std::greater<int>())) {
            auto heap_end = std::is_heap_until(received_priorities.begin(), received_priorities.end(),
                                               std::greater<int>());
            std::cout << "These Elements are min-heap: ";
            for (auto it = received_priorities.begin(); it != heap_end; ++it) {
                std::cout << *it << ", ";
            }
            std::cout << "\n";
            throw std::runtime_error("ERROR-> Not all Elements in min-heap");
        }

        std::cout << "<TEST PASSED>" << std::endl;

    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void test_insert_ordered(PriorityQueue &p) {
    try {
        std::cout << "-------- TESTING: bool insert(Element &e) --------" << std::endl;
        // Inserting Elements
        for (int i = 0; i < 10; i++) {
            Element e1;
            e1.name = strings[i];
            e1.priority = priorities[i];
            p.insert(e1);
        }

        std::cout << "Expecting Ascending: ";
        for (int i = 0; i < 10; i++) {
            std::cout << answer[i] << ":" << answer_priorities[i] << " ";
        }
        std::cout << "\n";
        std::cout << "Or Descending:       ";
        for (int i = 9; i >= 0; i--) {
            std::cout << answer[i] << ":" << answer_priorities[i] << " ";
        }
        std::cout << "\n";

        std::cout << "Received: ";
        for (int i = 0; i < 10; i++) {
            std::cout << p.pq[i].name << ":" << p.pq[i].priority << " ";
        }
        std::cout << "\n";

        // Check forward and reverse order
        bool reverse = true;
        bool forward = true;
        // Check if expected == received
        for (int i = 0; i < 10; i++) {
            if (p.pq[i].name != answer[i]) {
                forward = false;
            }
            if (p.pq[9 - i].name != answer[9 - i]) {
                reverse = false;
            }
        }

        if (reverse || forward) {
            std::cout << "<TEST PASSED>" << std::endl;
        } else {
            throw std::runtime_error("ERROR-> Not in correct order");
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests insert for PQLinkedList
// Different test due to not using the array pq
void test_insert_linked(PriorityQueue &p) {
    try {
        std::cout << "-------- TESTING: bool insert(Element &e) --------" << std::endl;
        //Inserting Elements
        for (int i = 0; i < 10; i++) {
            Element e1;
            e1.name = strings[i];
            e1.priority = priorities[i];
            p.insert(e1);
        }

        if (p.head == nullptr) {
            throw std::runtime_error("ERROR-> Head returns nullptr after insertion");
        }

        // Vector of received
        std::vector <Element> received;
        // Traverse through list and store Elements
        Node *dummy = p.head;
        while (dummy != nullptr) {
            received.push_back(dummy->data);
            dummy = dummy->next;
        }

        // Print expected and received
        std::cout << "Expected Ascending: ";
        for (int i = 0; i < 10; i++) {
            std::cout << answer[i] << ":" << answer_priorities[i] << " ";
        }
        std::cout << "\n";
        std::cout << "Or Descending:      ";
        for (int i = 9; i >= 0; i--) {
            std::cout << answer[i] << ":" << answer_priorities[i] << " ";
        }
        std::cout << "\n";

        std::cout << "Received: ";
        for (int i = 0; i < 10; i++) {
            std::cout << received[i].name << ":" << received[i].priority << " ";
        }
        std::cout << "\n";

        // Check forward and reverse order
        // Check forward and reverse order
        bool reverse = true;
        bool forward = true;
        // Check if expected == received
        for (int i = 0; i < 10; i++) {
            if (received[i].name != answer[i]) {
                forward = false;
            }
            if (received[9 - i].name != answer[9 - i]) {
                reverse = false;
            }
        }

        if (reverse || forward) {
            std::cout << "<TEST PASSED>" << std::endl;
        } else {
            throw std::runtime_error("ERROR-> Not in correct order");
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests if PriorityQueue remove() removes and returns correct elements
// Expects the element of the highest priority that satisfies FIFO
void test_remove(PriorityQueue &p) {
    try {
        std::cout << "------------- Testing: bool remove() -------------" << std::endl;
        Element expected1("Item1", 0);
        Element expected2("Item7", 0);
        Element expected3("Item2", 1);
        Element received1 = p.remove();
        Element received2 = p.remove();
        Element received3 = p.remove();

        if (!compare_elements(expected1, received1) || !compare_elements(expected2, received2) ||
            !compare_elements(expected3, received3)) {
            std::cout << "*NOTE: Tests if Elements are removed in correct order, FIFO is required here." << std::endl;
            std::cout << "Expected: " << expected1.name << " " << expected2.name << " " << expected3.name << std::endl;
            std::cout << "Received: " << received1.name << " " << received2.name << " " << received3.name << std::endl;
            throw std::runtime_error("ERROR -> Incorrect elements removed!");
        }
        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests if PriorityQueue size() returns correct size
void test_size(PriorityQueue &p) {
    try {
        // 10 Elements inserted in test_insert()
        // Expecting a size of 10
        std::cout << "--------------- Testing: int size() --------------" << std::endl;
        int received = p.size();
        int expected = 10;
        if (expected != received) {
            std::cout << "Expected: " << expected << std::endl;
            std::cout << "Received: " << received << std::endl;
            throw std::runtime_error("ERROR -> Incorrect size!");
        }
        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests if PriorityQueue del() removes all instances of the given element
// Tests for PQOrdered
void test_del_ordered(PriorityQueue &p) {
    try {
        // Inserts item11 twice
        // Expects both instances of item11 to be deleted
        std::cout << "--------- Testing: bool del(Element &e) ----------" << std::endl;
        // Insert two copies of Item11 and del both
        Element test("Item11", 8);
        p.insert(test);
        p.insert(test);
        bool tf = p.del(test);

        // Testing if returns true or false
        if (!tf) {
            throw std::runtime_error("ERROR-> del() returned false, Element(s) not deleted!");
        }

        for (int i = 0; i < p.size(); i++) {
            if (p.pq[i].name == "Item11") {
                throw std::runtime_error("ERROR-> Item11 still in the array");
            }
        }

        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests if PriorityQueue del() removes all instances of the given element
// Tests for PQLinked
void test_del_linked(PriorityQueue &p) {
    try {
        // Inserts item11 twice
        // Expects both instances of item11 to be deleted
        std::cout << "--------- Testing: bool del(Element &e) ----------" << std::endl;
        // Insert two copies of Item11 and del both
        Element test("Item11", 8);
        p.insert(test);
        p.insert(test);
        bool tf = p.del(test);

        // Testing if returns true or false
        if (!tf) {
            throw std::runtime_error("ERROR-> del() returned false, Element(s) not deleted!");
        }

        Node *dummy = p.head;
        std::vector <Element> received;
        while (dummy != nullptr) {
            received.push_back(dummy->data);
            dummy = dummy->next;
        }

        for (auto &i: received) {
            if (i.name == "Item11") {
                throw std::runtime_error("ERROR-> Item11 still in the array");
            }
        }

        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests if PriorityQueue del() removes all instances of the given element
// Tests for PQHeap
void test_del_heap(PriorityQueue &p) {
    try {
        // Inserts item11 twice
        // Expects both instances of item11 to be deleted
        std::cout << "--------- Testing: bool del(Element &e) ----------" << std::endl;
        // Insert two copies of Item11 and del both
        Element test("Item11", 8);
        p.insert(test);
        p.insert(test);
        bool tf = p.del(test);

        // Testing if returns true or false
        if (!tf) {
            throw std::runtime_error("ERROR-> del() returned false, Element(s) not deleted!");
        }

        for (int i = 0; i < p.size(); i++) {
            if (p.pq[i].name == "Item11") {
                throw std::runtime_error("ERROR-> Item11 still in the array");
            }
        }

        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests PriorityQueue peek()
// Expects the highest priority element returned
void test_peek(PriorityQueue &p) {
    try {
        std::cout << "------------- Testing: Element peek() ------------" << std::endl;
        Element expected("Item6", 1);
        Element received = p.peek();

        if (!compare_priority(expected, received)) {
            std::cout << "Expected: Element of priority " << expected.priority << std::endl;
            std::cout << "Received: Element of priority " << received.priority << std::endl;
            throw std::runtime_error("ERROR -> Incorrect element returned!");
        }
        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests PriorityQueue contains() function
void test_contains(PriorityQueue &p) {
    try {
        std::cout << "------- Testing: bool contains(Element &e) -------" << std::endl;
        Element e("Item1", 0);
        if (!p.contains(e)) {
            std::cout << "Expected: true" << std::endl;
            std::cout << "Received: false" << std::endl;
            throw std::runtime_error("ERROR -> Does not contain element!");
        }
        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Tests if PriorityQueue implementation correctly clears pq
// Tests if isEmpty() returns correctly
void test_clear_empty(PriorityQueue &p) {
    try {
        // Expects entire pq to only contain Elements with default constructor values
        std::cout << "-------------- Testing: void clear() -------------" << std::endl;
        p.clear();

        if (p.size() > 0) {
            throw std::runtime_error("Error -> Array not empty, size greater than zero! ");
        }
        std::cout << "<TEST PASSED>" << std::endl;

        // Tests if pq is empty after clearing pq
        std::cout << "------------- Testing: bool isEmpty() ------------" << std::endl;
        if (!p.isEmpty()) {
            std::cout << "Expected: true" << std::endl;
            std::cout << "Received: false" << std::endl;
            throw std::runtime_error("ERROR -> PQ is not empty!");
        }
        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Checks if isFull() returns correctly when full
void test_full_size(PriorityQueue &p) {
    try {
        // Fills pq with Elements then checks isFull()
        std::cout << "--------- Testing: virtual bool isFull() ---------" << std::endl;
        p.clear();
        for (int i = 0; i < CONSTRUCTOR_TEST_SIZE; i++) {
            Element e(std::to_string(i), 0);
            p.insert(e);
        }

        if (!p.isFull()) {
            std::cout << "Expected: true" << std::endl;
            std::cout << "Received: false" << std::endl;
            throw std::runtime_error("ERROR -> PQ is not full!");
        }

        std::cout << "<TEST PASSED>" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// Calls all tests for Linked List PriorityQueue
void test_PQLinkedList() {
    std::cout << "************** TESTING: PQLinkedList *************" << std::endl;
    test_constructors<PriorityQueue>();
    PriorityQueue test(CONSTRUCTOR_TEST_SIZE);
    test_insert_linked(test);
    test_size(test);
    test_contains(test);
    test_del_linked(test);
    test_remove(test);
    test_peek(test);
    test_clear_empty(test);
    test_full_size(test);
    std::cout << "*************** TESTING COMPLETE *****************" << std::endl;
}

// Calls all tests for Ordered PriorityQueue
void test_PQOrdered() {
    std::cout << "*************** TESTING: PQOrdered ***************" << std::endl;
    test_constructors<PriorityQueue>();
    PriorityQueue test(CONSTRUCTOR_TEST_SIZE);
    test_insert_ordered(test);
    test_size(test);
    test_contains(test);
    test_del_ordered(test);
    test_remove(test);
    test_peek(test);
    test_clear_empty(test);
    test_full_size(test);
    std::cout << "*************** TESTING COMPLETE *****************" << std::endl;
}

// Calls all tests for Heap PriorityQueue
void test_PQHeap() {
    std::cout << "**************** TESTING: PQHeap *****************" << std::endl;
    test_constructors<PriorityQueue>();
    PriorityQueue test(CONSTRUCTOR_TEST_SIZE);
    test_insert_heap(test);
    test_size(test);
    test_contains(test);
    test_del_heap(test);
    test_remove(test);
    test_peek(test);
    test_clear_empty(test);
    test_full_size(test);
    std::cout << "*************** TESTING COMPLETE *****************" << std::endl;
}