#pragma once
#include <iostream>
using namespace std;

template <class T>
class ListNode
{
public:
    T data;
    ListNode<T> *next;
    ListNode<T> *prev;

    //constructors
    ListNode();
    ListNode(T d);
    ~ListNode();
};

template <class T>
ListNode<T>::ListNode() {}

template <class T>
ListNode<T>::ListNode(T d)
{
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T>
ListNode<T>::~ListNode()
{
    next = NULL;
    prev = NULL;
}

