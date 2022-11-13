// PQOrderedArray.cpp

// This file is for implementation of the ordered array implementation
// of the priority queue.

#include <iostream>
#include <string>
#include <memory>
#include "PriorityQueue.h"
#include "TestDriver.h"
using namespace std;

// Default constructor
PriorityQueue::PriorityQueue()
{
    max_capacity = DEFAULT_MAX_CAPACITY;
    pq = make_unique<Element[]>(max_capacity);
}

// Parameterized constructor
PriorityQueue::PriorityQueue(int size)
{
    max_capacity = size;
    pq = make_unique<Element[]>(max_capacity);
}

// Inserts a new object into the priority queue. Returns true if
// the insertion is successful. If the PQ is full, the insertion
// is aborted, and the method returns false.
bool PriorityQueue::insert(Element &element)
{
    if (isFull())
        return false;

    // The first object inserted into the PQ will have the highest priority
    // because it has the lowest FIFO value
    if (isEmpty())
        element.fifo = 1;
    else
        element.fifo = pq[0].fifo + 1;

    int index = size();
    pq[index] = element;

    // Iterate through the elements of the PQ
    for (int i = index - 1; i >= 0; i--)
    {
        if (pq[i].priority >= pq[index].priority)
            break;

        // Swap the elements if the priority of the next element is higher
        Element temp = pq[i];
        pq[i] = pq[index];
        pq[index] = temp;

        index--;
    }
    return true;
}

// The object of the highest priority must be the one returned by the
// remove() method; and if multiple objects have the same priority,
// the one in the queue the longest shall be returned, ie, FIFO
// return order must be preserved for objects of identical priority.
// Returns the default constructed Element if the PQ is empty.
Element PriorityQueue::remove()
{
    if (isEmpty())
        return Element();

    Element temp = pq[0];
    int index = size() - 1;

    // Move the last object of the list to the first position and decrement the size of the list
    pq[0] = pq[index];
    pq[index] = Element();

    // Iterate through the elements of the PQ
    for (int i = 1; i < size(); i++)
    {
        // If the priority of the previous element is higher, break
        if (pq[i - 1].priority >= pq[i].priority)
            break;

        // Swap the elements if the priority of the next element is higher
        Element temp = pq[i];
        pq[i] = pq[i - 1];
        pq[i - 1] = temp;
    }
    return temp;
}

// Deletes all instances of the parameter from the PQ if found, and
// returns true. Returns false if no match to the parameter obj is found.
bool PriorityQueue::del(Element &element)
{
    if (isEmpty())
        return false;

    // Iterate through the elements of the PQ
    for (int i = 0; i < size(); i++)
    {
        // If the element is found, remove it from the PQ
        if (pq[i].name == element.name)
        {
            int index = size() - 1;
            pq[i] = pq[index];
            pq[index] = Element();

            // Iterate through the elements of the PQ
            for (int i = 0; i < size(); i++)
            {
                // If the priority of the previous element is higher, break
                if (pq[i - 1].priority >= pq[i].priority)
                    break;

                // Swap the elements if the priority of the next element is higher
                Element temp = pq[i];
                pq[i] = pq[i - 1];
                pq[i - 1] = temp;
            }
            return true;
        }
    }
    return false;
}

// Returns the object of highest priority in the PQ; if multiple
// objects have the same highest priority, return the one that has
// been in the PQ the longest, but does NOT remove it.
// Returns default constructed Element if the PQ is empty.
Element PriorityQueue::peek()
{
    if (isEmpty())
        return Element();

    return pq[0];
}

// Returns true if the pq contains the specified element
bool PriorityQueue::contains(Element &element)
{
    if (isEmpty())
        return false;

    // Iterate through the elements of the PQ
    for (int i = 0; i < size(); i++)
    {
        // If the element is found, return true
        if (pq[i].name == element.name)
            return true;
    }
    return false;
}

// Returns the number of objects currently in the PQ.
int PriorityQueue::size()
{
    int size = 0;

    // Iterate through the elements of the PQ
    for (int i = 0; i < max_capacity; i++)
    {
        // If the value of the element is not the default value, increment the size
        if (pq[i].priority != -1)
            size++;
    }
    return size;
}

// Returns the PQ to its default state.
void PriorityQueue::clear()
{
    for (int i = 0; i < max_capacity; i++)
        pq[i] = Element();
}

// Returns true if the PQ is empty
bool PriorityQueue::isEmpty()
{
    return size() == 0;
}

// Returns true if the PQ is full
bool PriorityQueue::isFull()
{
    return size() == max_capacity;
}

// Run the test
// int main()
// {
//     // Test the ordered array implementation
//     PriorityQueue pq1(5);
//     Element element1("element 1", 1);
//     Element element2("element 2", 2);
//     Element element3("element 3", 3);
//     Element element4("element 4", 4);
//     Element element5("element 5", 5);
//     Element element6("element 6", 1);

//     pq1.insert(element1);
//     pq1.insert(element2);
//     pq1.insert(element3);
//     pq1.insert(element4);
//     pq1.insert(element5);
//     pq1.insert(element6);

//     cout << "The elements of the first PQ are: " << endl;
//     while(!pq1.isEmpty())
//     {
//         Element temp = pq1.remove();
//         cout << temp.name << " " << temp.priority << endl;
//     }
//     cout << endl;

//     // Test the linked list implementation
//     PriorityQueue pq2(5);
//     Element element7("element 1", 1);
//     Element element8("element 2", 2);
//     Element element9("element 3", 3);
//     Element element10("element 4", 4);
//     Element element11("element 5", 5);
//     Element element12("element 6", 1);

//     pq2.insert(element7);
//     pq2.insert(element8);
//     pq2.insert(element9);
//     pq2.insert(element10);
//     pq2.insert(element11);
//     pq2.insert(element12);

//     cout << "The elements of the second PQ are: " << endl;
//     while(!pq2.isEmpty())
//     {
//         Element temp = pq2.remove();
//         cout << temp.name << " " << temp.priority << endl;
//     }
//     cout << endl;

//     // Test the binary heap implementation
//     PriorityQueue pq3(5);
//     Element element13("element 1", 1);
//     Element element14("element 2", 2);
//     Element element15("element 3", 3);
//     Element element16("element 4", 4);
//     Element element17("element 5", 5);
//     Element element18("element 6", 1);

//     pq3.insert(element13);
//     pq3.insert(element14);
//     pq3.insert(element15);
//     pq3.insert(element16);
//     pq3.insert(element17);
//     pq3.insert(element18);

//     cout << "The elements of the third PQ are: " << endl;
//     while(!pq3.isEmpty())
//     {
//         Element temp = pq3.remove();
//         cout << temp.name << " " << temp.priority << endl;
//     }
//     cout << endl;

//     return 0;
// }

int main()
{
    test_PQOrdered();
    return 0;
}
