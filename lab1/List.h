/*
 * Name:
 * Date Submitted: 1/30/23
 * Lab Section:
 * Assignment Name:
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

private:
    Node<T> * start; //pointer to the first node in this list
    int mySize;  //size (or length) of this list

public:
    List();
    ~List();
    int size();
    bool empty();
    void insertStart(T);
    void insertEnd(T);
    void insertAt(T, int);
    void removeStart();
    void removeEnd();
    void removeAt(int);
    T getFirst();
    T getLast();
    T getAt(int);
    int find(T);

    //Print the name and this list's size and values to stdout
    //This function is already implemented (no need to change it)
    void print(string name){
        cout << name << ": ";
        cout << "size = " << size();
        cout << ", values = ";
        Node<T> * iterator = start;
        while(iterator != nullptr){
            cout << iterator->value << ' ';
            iterator = iterator->next;
        }
        cout << endl;
    }

}; //end of class interface (you may modify the code below)

//Implement all the functions below
//Construct an empty list by initializing this list's instance variables
template <class T>
List<T>::List(){
    start = nullptr;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
    Node<T> *ptr = start; //point to the head node
    while(ptr != nullptr){ //while the next node exists (is not nullptr)
        Node<T> *temp = ptr; //make a temp pointer to hold the last node location
        ptr = ptr->next; //find where the next node is
        delete temp; //delete the last node
    }
    delete ptr;
}

//Return the size of this list
template <class T>
int List<T>::size(){
    int counter = 0; //initialize a counter variable at 0
    Node<T> *ptr = start; //make a pointer to the head node of the linked list

    while(ptr != nullptr){ //while (not at the end of the list), iterate through and add 1 to the counter for each item in the list
        ptr = ptr->next;
        counter++;
    }
    mySize = counter;
    return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
    if (start == nullptr){ //if the next item that start references is the nullptr, that means that there is nothing else in the list. return true.
        return true;
    }
    else {
        return false;
    }
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
    auto *newStart = new Node<T>(value);
    newStart->value = value;
    newStart->next = start;
    start = newStart;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value) {
    auto *newNode = new Node<T>(value);
    if (start == nullptr) {
        start = newNode;
    } else {
        Node<T> *current = start;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
    auto *newNode = new Node<T>(value);
    newNode->value = value;
    newNode->next = nullptr;

    if (j == 0) {
        newNode->next = start;
        start = newNode;
        return;
    }

    Node<T> *current = start;
    for (int i = 0; i < j-1; i++) {
        if (current == nullptr) {
            return;
        }
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart() {
    if (start != nullptr) {
        Node<T> *temp = start;
        start = start->next;
        delete temp;
    }
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
    Node<T> *ptr = start;

    if (start == nullptr) {
        return;
    }

    if (start->next == nullptr) {
        delete start;
        start = nullptr;
        return;
    }

    while(ptr->next->next != nullptr){ //while the node after the current node's next value is not nullptr, continue traversing
        ptr = ptr->next;
    }

    delete ptr->next;
    ptr->next = nullptr;
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
    if (start == nullptr) {
        return;
    }

    if (j == 0) {
        Node<T> *temp = start;
        start = start->next;
        delete temp;
        return;
    }

    Node<T> *ptr = start;
    for (int i = 0; i < j-1; i++) {
        if (ptr == nullptr || ptr->next == nullptr) {
            return;
        }
        ptr = ptr->next;
    }

    Node<T> *temp = ptr->next;
    ptr->next = ptr->next->next;
    delete temp;
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
    return start->value;
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
    Node<T> *ptr;
    ptr = start;

    while(ptr->next != nullptr) {
        ptr = ptr->next;
    }
    return ptr->value;
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
    Node<T> *ptr;
    ptr = start;

    for (int i = 0; i < j; i++) {
        if (ptr == nullptr) {
            return T();
        }
        ptr = ptr->next;
    }
    return ptr->value;
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key) {

    if (start == nullptr) { //list is empty
        return -1;
    }

    int position = 0; //counter for position
    Node<T> *ptr = start; //pointer for the list, place it at the start of the list
    while (ptr->next != nullptr) {
        if (ptr->value == key) {
            return position;
        }
        position++;
        ptr = ptr->next;
    }
    return -1;
}