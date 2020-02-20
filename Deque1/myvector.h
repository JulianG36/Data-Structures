//Name: Julian Gonzales
//NetID: Jgonz96
//Assignent: Project 1
//Description: Implements both nodes and arrays effectively making the array increase by desired amount when full without reallocating the entire array
//the lookup time is slowed down depending on the size of array in each node. allocating ten thousand elements in an array per node in a set containing 2 million elements
//is much faster than only allocating 10 elements in an array per node. as search time is at most (Number of elements in set)/(Number of elements in each node) iterations
//much faster than a regular linked list 
//appending to the end is effectively doubled in speed compared to a regular vector from tests containing large sets of data
//deletion is slower compared to a vector
//this structure would be perfect for a situation where one is appending large amounts of data without the need to insert in between
#pragma once

#include <iostream>  // print debugging
#include <cstdlib>   // malloc, free
#include <vector>
using namespace std;
template<typename T>
//Node is similar to  vector but does not dynamically increase in size and points to another node
class Node{
    private:
    T* A;
    int Size;
    int Capacity;

    public:
    Node<T> *next;

    Node(){
        A = new T[10];
        Size = 0;
        Capacity = 10;
        next = nullptr;
    }
    Node(int initial_size){
        A = new T[initial_size];
        Size = 0;
        Capacity = initial_size;
        next = nullptr;
    }
    void setNext(Node<T> *node){
        next = node;
    }
    int size() const
    {
        return Size;
    }
    void reduceSize(){
        Size--;
    }
    int capacity(){
        return Capacity;
    }
    T& at(int i)
    {
        return A[i];
    }
    //does not increase in size unlike a vector
    void push_back(T value)
    {
        A[Size] = value;
        Size++;
    }
};


template<typename T>
class myvector
{
private:
    Node<T>* head;
    Node<T>* tail;
    int  numNodes;
    int  TotalSize;
    int  TotalCapacity;
    int  arraySizes;

public:
    //arraySizes is used to set what the size in each node should be
    myvector(){
        head = new Node<T>(10);
        tail = head;
        numNodes = 1;
        TotalSize = 0;
        TotalCapacity = 10;
        arraySizes = 10;
    }
    myvector(int initial_size){
        head = new Node<T>(initial_size);
        tail = head;
        numNodes = 1;
        TotalSize = initial_size;
        TotalCapacity = initial_size;
        arraySizes = initial_size;
    }
    myvector(const myvector& other){
        head = new Node<T>(other.arraySizes);
        tail = head;
        numNodes = 1;
        arraySizes = other.arraySizes;
        TotalSize = 0;
        TotalCapacity = arraySizes;
        Node<T> *temp = other.head;
        //creates all the nodes needed in a similar style to push_back except this one goes through all the nodes in other
        while(temp!=nullptr){
            if(TotalCapacity == TotalSize){
                TotalCapacity = TotalCapacity+arraySizes;
                Node<T> *newNode = new Node<T>(arraySizes);
                if(numNodes == 0){
                    head->setNext(newNode);
                    tail = newNode;
                    numNodes++;
                }else{
                    tail->setNext(newNode);
                    numNodes++;
                }
                tail = newNode;
            }
            for(int i = 0; i < arraySizes; i++){
                //making sure i dont put the address into the other Node
                int val = temp->at(i);
                tail->at(i) = val; 
                TotalSize++;
            }
            temp = temp->next;
        }
    }
    //drops tail when not in use anymore. when its size reaches zero
    void dropTail(){
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        while(curr->next != nullptr){
            prev = curr;
            curr = curr->next;
        }
        if(prev == nullptr){
            head = new Node <T>(arraySizes);
            tail = head;
        }else{
            TotalCapacity = TotalCapacity - arraySizes;
            numNodes--;
            prev->next = nullptr;
            tail = prev;
        }
    }

    T erase(int i){
        if(i >= TotalSize){
            return -1;
        }
        int result = at(i);
        Node<T> *temp = head;
        int sum = 0 + temp->capacity();
        int nodesTravesed = 1;
        while(sum <= i){
            temp = temp->next;
            sum = sum + temp->capacity();
            nodesTravesed++;
        }
        int val = temp->capacity()-1 - (sum-i-1);
        int index = val;
        for(int i = nodesTravesed; i < numNodes+1; i++){
            for(int k = val; k < arraySizes; k++){
                if(k == arraySizes-1 && temp->next != nullptr){
                    T& prevNodeAddress = temp->at(k);
                    temp = temp->next;
                    prevNodeAddress = temp->at(0);
                    val = 0;          
                }else if(k+1 < arraySizes){
                    temp->at(k) = temp->at(k+1);
                }
            }
        }
        //set last element to zero
        temp->reduceSize();
        //drops tail if needed this so that push back doesnt push onto the very last node instead drops it and pushes onto the correct one
        if(temp->size() == 0){
            dropTail();
        }
        TotalSize--;
        temp->at(temp->size()) = 0;
        return result;
    }
    T& operator[](int i){
        return at(i);
    }
    //returns array from i to j
    T* rangeof(int i, int j){
        T* A = new T[j-i+1];
        int k = 0;
        for(i; i <= j; i++){
            cout << at(i)<< endl;
            A[k] = at(i);
            k++; 
        } 
        return A;
    }
    int size(){
        return TotalSize;
    }
    //adds a node to the end of the list when full
    void push_back(T value){
        if(TotalCapacity == TotalSize){
            TotalCapacity = TotalCapacity+arraySizes;
            Node<T> *newNode = new Node<T>(arraySizes);
            if(numNodes == 0){
                head->setNext(newNode);
                tail = newNode;
                numNodes++;

            }else{
                tail->setNext(newNode);
                numNodes++;

            }
            tail = newNode;
        }
        tail->push_back(value);
        TotalSize++;
    }
    //displays sizes of each node more for debugging
    void allSizes(){
        Node<T> *temp = head;
        while(temp->next != nullptr){
            cout<<temp->size()<< endl;
            
            temp = temp->next;

        }
    }  
    //returns the array element by checking the size of each node and sums it until it has passed it
    T& at(int i){
        Node<T> *temp = head;
        int sum = 0 + temp->capacity();
        while(sum <= i){
            temp = temp->next;
            sum = sum + temp->capacity();
        }
        //subtracting the sum and i from the capacity of the node array gives the position of the element in the array, -1 because counting zero also
        T& result = temp->at(temp->capacity()-1 - (sum-i-1));
        return result;
    }
};


//Much faster than vector :)))))))))
//cut appending in half
