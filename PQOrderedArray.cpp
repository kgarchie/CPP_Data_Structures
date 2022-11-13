// PQOrderedArray.cpp - duplicate of PQOrdered.cpp - created due to discrapancies in naming of the files in the write up and the files provided in the starter code.
#include "TestDriver.h"
#include "PriorityQueue.h"
#include <iostream>


// make_unique is a C++14 feature so we make our own implementation
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// Constructor
PriorityQueue::PriorityQueue()
{
    max_capacity = DEFAULT_MAX_CAPACITY;
    pq = std::make_unique<Element[]>(DEFAULT_MAX_CAPACITY);
}

// Parameterized constructor
PriorityQueue::PriorityQueue(int size)
{
    max_capacity = size;
    pq = std::make_unique<Element[]>(size);
}

bool PriorityQueue::insert(Element &element)
{
    if (size() == max_capacity)
    {
        return false;
    }

    if (size() == 0)
    {
        pq[0] = element;
        return true;
    }

    // find correct insertion point
    int insertIndex = 0;
    // compare priorities
    if (pq[0].priority < element.priority)
    {
    }
    else if (pq[0].priority > element.priority)
    {
    }
    else
    {
        // compare fifo
        if (pq[0].fifo < element.fifo)
        {
        }
        else if (pq[0].fifo > element.fifo)
        {
        }
    }
    // insert element
    pq[insertIndex] = element;
    return true;
}

Element PriorityQueue::remove()
{
    if (isEmpty())
    {
        Element element;
        return element;
    }

    Element element = pq[0];
    // shift all other cells down by one
    for (int i = 0; i < size() - 1; i++)
    {
        pq[i] = pq[i + 1];
    }

    return element;
}

bool PriorityQueue::del(Element &element)
{
    if (isEmpty())
    {
        return false;
    }

    bool isFound = false;
    // find index of element to delete
    int i = 0;
    for (; i < size(); i++)
    {
        if (pq[i].name == element.name)
        {
            isFound = true;
            break;
        }
    }

    // if element is not found, return false
    if (!isFound)
    {
        return false;
    }

    // shift all other cells down by one
    for (int j = i; j < size(); j++)
    {
        pq[j] = pq[j + 1];
    }

    return true;
}

Element PriorityQueue::peek()
{
    if (isEmpty())
    {
        Element element;
        return element;
    }

    return pq[0];
}

bool PriorityQueue::contains(Element &element)
{
    for (int i = 0; i < size(); i++)
    {
        if (pq[i].name == element.name)
        {
            return true;
        }
    }
    return false;
}

int PriorityQueue::size()
{
    // iterate through all elements
    int count = 0;
    for (int i = 0; i < max_capacity; i++)
    {
        if (pq[i].name != "None")
        {
            count++;
        }
    }
    return count;
}

void PriorityQueue::clear()
{
    for (int i = 0; i < max_capacity; i++)
    {
        pq[i].name = "None";
        pq[i].priority = -1;
    }
}

bool PriorityQueue::isEmpty()
{
    return size() == 0;
}

bool PriorityQueue::isFull()
{
    return size() == max_capacity;
}

int main()
{
    test_PQOrdered();
    return 0;
}

/*
uncomment the below code to quickly test your implementation
*/

// int main() {
//     PriorityQueue queue;
//     Element element = Element("test", 0);
//     queue.insert(element);
//     element = Element("test2", 0);
//     queue.insert(element);
//     element = Element("test3", 1);
//     queue.insert(element);

//     std::cout << queue.peek().name << std::endl;
//     queue.remove();
//     std::cout << queue.peek().name << std::endl;
//     queue.remove();
//     std::cout << queue.peek().name << std::endl;
//     queue.remove();
// }