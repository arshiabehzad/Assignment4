#pragma once
#include "ListNode.h"
using namespace std;

template <class T>
class DoubleLinkedList
{
    public:
        //front and back nodes
        ListNode<T> *front;
        ListNode<T> *back;

        unsigned int size;

        DoubleLinkedList();
        ~DoubleLinkedList();

        void insertFront(T d);
        void insertBack(T d);
        T removeFront();
        T removeBack();
        T deletePos(int position);
        int find(T d);

        bool isEmpty();
        void printList();
        unsigned int getSize();

        //void remove(T d);
};


//DoubleLinkedList implementation

template <class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    size = 0;
    front = NULL;
    back = NULL;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    //iterate through the list
    ListNode<T>* current = front;
    ListNode<T>* previous = front;

    while(current != NULL)
    {
        previous = current;
        current = current->next;
        previous = NULL;
    }
}

template <class T>
void DoubleLinkedList<T>::insertFront(T d)
{
    ListNode<T> *node = new ListNode<T>(d);
    if (size == 0)
    {
        back = node;
    }
    else
    {
        //not an empty list
        node->next = front;
        front->prev = node;
    }
    front = node;
    size++;
}

template <class T>
T DoubleLinkedList<T>::removeFront()
{
    if(isEmpty())
    {
        throw runtime_error("empty");
    }
    T tmp = front->data;
    ListNode<T> *ft = front;

    if (size == 1)
    {
        //it's the only node in the list
        back = NULL;
    }
    else
    {
        //more than one element
        front->next->prev = NULL;
    }
    front = front->next;
    ft->next = NULL;
    delete ft;
    size--;

    return tmp;
}

template <class T>
void DoubleLinkedList<T>::insertBack(T d)
{
    ListNode<T> *node = new ListNode<T>(d);
    if (isEmpty())
    {
        front = node;
    }
    else
    {
        //not an empty list
        back->next = node;
        node->prev = back;
    }
    back = node;
    size++;
}

template <class T>
T DoubleLinkedList<T>::removeBack()
{
    if(isEmpty())
    {
        throw runtime_error("empty");
    }

    ListNode<T>* backTemp = back;
    

    if (size == 1)
    {
        back = NULL;
    }
    else
    {
        back->previous->next = NULL;
    }
    back = back->previous;
    T temp = backTemp->data;
    backTemp->previous = NULL;
    delete backTemp;
    size--;
    return temp;
}

template <class T>
T DoubleLinkedList<T>::deletePos(int pos)
{
    int index = 0;
    ListNode<T>* current = front;
    ListNode<T>* previous = front;

    while (index != pos)
    {
        previous = current;
        current = current->next;
        index++;
    }
}

template <class T>
int DoubleLinkedList<T>::find(T d)
{
    int index = 0;
    ListNode<T>* current = front;

    while (current != NULL)
    {
        if (current->data == d)
        {
            break;
        }
        index++;
        current = current->next;
    }
    if (current = NULL)
    {
        index = -1;
    }
    return index;
}

//helper function 
template <class T>
void DoubleLinkedList<T>::printList()
{
    ListNode<T>* current = front;
    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->next;
    }
}

template <class T>
unsigned int DoubleLinkedList<T>::getSize()
{
    return size;
}

/*
template <class T>
void DoubleLinkedList<T>::remove(T d)
{
    //check if list is not empty before attempting to remove
    ListNode<T> *curr = front;
    while (curr->data != d)
    {
        curr = curr->next;
        if (curr = NULL) // We did not find the value
            return NULL;
    }
    //if we get to this point it means we found it
    //let's check if the node is the front
    if (curr == front)
    {
        front = curr->next;
    }
    else
    {
        //it's not the front
        curr->prev->next == curr->next;
    }

    if (curr == back)
    {
        back = curr->prev;
    }
    else
    {
        //its not the back
        curr->next->prev == curr->prev;
    }
    curr->next = NULL;
    curr->prev = NULL;
    size--;

}*/

template <class T>
bool DoubleLinkedList<T>::isEmpty()
{
    if(size==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}