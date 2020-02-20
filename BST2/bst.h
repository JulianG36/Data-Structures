
//
// Julian Gonzales
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
//Description: Binary search tree
//


#pragma once

#include <iostream>
#include <algorithm>  // std::max
#include <string>
using namespace std;

struct MovieData{
    int id;
    int PubYear;
    string name;
    int Num5Stars;
    int Num4Stars;
    int Num3Stars;
    int Num2Stars;
    int Num1Star;
  };

template<typename TKey, typename Data>
class binarysearchtree
{

private:
  struct NODE
  {
    TKey  Key;
    Data*  data;
    NODE* Left;
    NODE* Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  int   NumReviews;
  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
    void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " ";
        _inorder(cur->Right);
     }
  }
  int max(int left, int right){
      if(left > right){
         return left;
      }else{
         return right;
      }
  }
  int _height(NODE* cur){
      if(cur == nullptr){
         return 0;
      }else{
         return 1 + max(_height(cur->Left), _height(cur->Right));  
      }
  }
  //copy helper function
  void _copy(NODE* other){
    if(other == nullptr){
      return; 
    }else{
      MovieData* newData= new MovieData;
      newData->id = other->data->id;
      newData->name = other->data->name;
      newData->Num1Star= other->data->Num1Star;
      newData->Num2Stars = other->data->Num2Stars;
      newData->Num3Stars = other->data->Num3Stars;
      newData->Num4Stars = other->data->Num4Stars;
      newData->Num5Stars = other->data->Num5Stars;
      insert(other->Key, *newData);
      _copy(other->Left);
      _copy(other->Right);
    }
    
    
  }
public:

  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
    NumReviews = 0;
  }
  //creates another copy doesnt point to same data
  binarysearchtree(binarysearchtree& other){
    Root = nullptr;
    Size = 0;
    NumReviews = other.NumReviews;
    if(other.Root == nullptr){
      return;
    }else{
      MovieData* newData= new MovieData;
      newData->id = other.Root->data->id;
      newData->name = other.Root->data->name;
      newData->Num1Star= other.Root->data->Num1Star;
      newData->Num2Stars = other.Root->data->Num2Stars;
      newData->Num3Stars = other.Root->data->Num3Stars;
      newData->Num4Stars = other.Root->data->Num4Stars;
      newData->Num5Stars = other.Root->data->Num5Stars;
      insert(other.Root->Key, *newData);
      _copy(other.Root->Left);
      _copy(other.Root->Right);

    }

    
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }
  int numReviews()
  {
    return NumReviews;
  }
  void numReviewsPlusOne(){
    NumReviews++;
  }

  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  {
     if(Root == nullptr){
      return -1;
     }else{
      return max(_height(Root->Left),  _height(Root->Right));
     }   
    //
    // TODO:
    //
    
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  bool search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return true;

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
  
    // if get here, not found
    return false;
  }
  Data* searchData(TKey key){
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if(cur->Key == key){
        return cur->data;
      }   
      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
    return nullptr;
  }


  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //s
  void insert(TKey key, Data & data)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;
    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }    

    //inserts after making sure it doesnt exist
    cur = Root;
    NODE* node = new NODE;
    node->Key = key;
    node->data = & data;
    node->Right = nullptr;
    node->Left = nullptr;
    if(cur == nullptr){
      Root = node;
      Size++;
    }
    while(cur != nullptr){  
      if(key < cur->Key){
            if(cur->Left == nullptr){
               cur->Left = node;
               Size++;
               return;
            }else{
               cur = cur->Left;
            }
      }else{
            if(cur->Right == nullptr){
               cur->Right = node;
               Size++;
               return;
            }
               cur = cur->Right;
      }
    }
  }
  void inorder()
  {
     cout << "Inorder: ";
     
     _inorder(Root);
     
     cout << endl;
  }
};




