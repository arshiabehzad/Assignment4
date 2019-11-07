#pragma once
#include <iostream>
#include "DoubleLinkedList.h"
using namespace std;

template <class T>
class GenQueue
{
public:
    GenQueue();
    ~GenQueue();

    //core functions
    void insert(T d);
    T remove();

    //aux functions
    T peek();
    bool isFull();
    bool isEmpty();
    int getSize();

    //vars
    int head; //aka front
    int rear; //aka tail
    int size;
    int numElements;

    DoubleLinkedList<T>* lQueue;
};

template <class T>
GenQueue<T>::GenQueue()
{
    lQueue = new DoubleLinkedList<T>();
}

template <class T>
GenQueue<T>::~GenQueue()
{
    delete lQueue; 
}

template <class T>
void GenQueue<T>::insert(T d)
{
    //add error checking
    lQueue->insertBack(d);
}

template <class T>
T GenQueue<T>::remove()
{
    //error checking
    return lQueue->removeFront();
}

template <class T>
T GenQueue<T>::peek()
{
    return lQueue->front->data;
}

template <class T>
bool GenQueue<T>::isFull()
{
    return (numElements == size);
}

template <class T>
bool GenQueue<T>::isEmpty()
{
    if(lQueue->getSize() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

template <class T>
int GenQueue<T>::getSize()
{
    return lQueue->getSize();
}