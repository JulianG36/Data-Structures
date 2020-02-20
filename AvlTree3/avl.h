//Name: Julian
//Class: CS 251
//Description: avl tree class that balances and also returns the distance between two nodes


#pragma once

#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

template<typename TKey, typename TValue>
class avltree
{
private:
  struct NODE
  {
    TKey   Key;
    TValue Value;
    int    Height;
    NODE*  Left;
    NODE*  Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

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
      cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
      _inorder(cur->Right);
    }
  }
  //
  // _copytree:
  //
  // Given a tree, inserts the (key, value) pairs into *this* tree.
  //
	void _copytree(NODE* cur){
	if (cur == nullptr)
		  return;
	else{
	  //
	  // to copy and build an exact copy, we need to "visit" cur
	  // first and insert that (key, value) pair first.  That way
	  // all the nodes to the left will properly go to the left,
	  // all the node to the right will properly go to the right.
	  //
		  insert(cur->Key, cur->Value);
		  _copytree(cur->Left);
		  _copytree(cur->Right);
		}
	}
    void _destruct(NODE* cur){
		if (cur == nullptr)
			return;
		else {
			_destruct(cur->Left);
			_destruct(cur->Right);
			delete cur;
			return;
		}
	}
	void _inorder_keys(NODE* cur, std::vector<TKey>& V)
	{
		if (cur == nullptr)
		  return;
		else{
			_inorder_keys(cur->Left, V);
			V.push_back(cur->Key);
			_inorder_keys(cur->Right, V);
		}
	}

	void _inorder_values(NODE* cur, std::vector<TValue>& V){
		if (cur == nullptr)
		  return;
		else{
			_inorder_values(cur->Left, V);
			V.push_back(cur->Value);
			_inorder_values(cur->Right, V);
		}
	}

	void _inorder_heights(NODE* cur, std::vector<int>& V)
	{
	if (cur == nullptr)
	  return;
	else
	{
	  _inorder_heights(cur->Left, V);
	  V.push_back(cur->Height);
	  _inorder_heights(cur->Right, V);
	}
	}
	void updateHeights(NODE* node){
		int HL = 0;
		int HR = 0;
		if(node->Left == nullptr){
			HL =  -1;
		}else{
			HL = node->Left->Height;
		}
		if(node->Right == nullptr){
			HR = -1;
		}else{
			HR = node->Right->Height;
		}
		node->Height = 1 + max(HL, HR);
	}
	int getBalance(NODE* node){
		int HR = -1;
		if(node->Right != nullptr){
			HR = node->Right->Height;
		}
		int HL = -1;
		if(node->Left != nullptr){
			HL = node->Left->Height;
		}
		return HL-HR;
	}



  void _RightRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);
    NODE* L = N->Left;
    NODE* B = L->Right;
    
    N->Left = B;
    L->Right = N;
    
    if(Parent == nullptr){
      Root = L;
    }else if(Parent->Key > L->Key){
      Parent->Left = L;
    }else{
      Parent->Right = L;
    }
    
	updateHeights(N);
	updateHeights(L);
    //
    // TODO
    //
    
  }

  void _LeftRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and R must exist
    assert(N->Right != nullptr);
    NODE* L = N->Right;
    NODE* B = L->Left;
    
    N->Right = B;
    L->Left = N;
    
    if(Parent == nullptr){
      Root = L;
    }else if(Parent->Key > L->Key){
      Parent->Left = L;
    }else{
      Parent->Right = L;
    }
    
    updateHeights(N);
    updateHeights(L);
  }
  //Checks the four cases for rotation and desides which to do
  void _RotateToFix(NODE* Parent, NODE* cur){
	  if(getBalance(cur) == 2){
		if(getBalance(cur->Left) == -1){
				_LeftRotate(cur, cur->Left);
			}
			_RightRotate(Parent, cur);
			cout << "Right" << endl;
		}else if(getBalance(cur) == -2){
			if(getBalance(cur->Right) == 1){
				_RightRotate(cur, cur->Right);
			}
			_LeftRotate(Parent, cur);
		}
  }
  //checks the distance from current to the following node if they are on the same side of the tree
  int _distanceFromCur(NODE* cur, int target, int count){
	  if(cur == nullptr){
			return -1;
	  }else if(cur->Key == target){
			return 0;
	  }else if(cur->Key > target){
			int val = _distanceFromCur(cur->Left,  target, count);
			if(val == -1){
				return -1;
			}else{
				return val+1;
			}
	  }else{
			int val = _distanceFromCur(cur->Right, target, count);
			if(val == -1){
				return -1;
			}else{
				return val+1;
			}
	  }
  }
  //checks the distance if they are on opposite sides of the tree
  int _distanceOposite(NODE* cur, int val1, int val2){
	  int count1 = _distanceFromCur(cur->Left, val1, 0);
	  int count2 = _distanceFromCur(cur->Right, val2, 0);
	  if(count1 == -1 || count2 == -1){
		  return -1;
	  }else{
		  return count1+count2+2;
	  }
  }
  //recursilvely checks and finds the distance in the tree in log(n) time
  int _distance(NODE* cur, int val1, int val2){
	  int count = -1;
	  if(cur == nullptr){
		  return count;
	  }else if(cur->Key == val1){
		  count = _distanceFromCur(cur, val2, 0);
	  }else if(cur->Key == val2){
		count = _distanceFromCur(cur, val1, 0);
	  }else if(val1 < cur->Key && val2 > cur->Key){ // if they are on the left and right side of the current node
		  count = _distanceOposite(cur, val1, val2);
	  }else if(val2 < cur->Key && val1 > cur->Key){ //if they are on the opposite but flipped
		  count = _distanceOposite(cur, val2, val1);
	  }else if(val1 < cur->Key && val2 < cur->Key){ //if they are on the left of the current sub tree
		  count = _distance(cur->Left, val1, val2);
	  }else if(val1 > cur->Key && val2 > cur->Key){ //if they are on the right of the the current sub tree
		  count = _distance(cur->Right, val1, val2);
	  }
	  return count;
  }
public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avltree()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor:
  //
  avltree(avltree& other)
  {
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
  }

  virtual ~avltree(){
	  _destruct(Root);
    //
    // TODO:
    //
  }
  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size(){
    return Size;
  }
  //
  // height
  //
  // Returns the height of tree; the height of an empty tree is
  // defined as -1.
  //
  int height()
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning a pointer to the 
  // value if found and nullptr if not.  We return a pointer so the caller
  // may update the underlying value if needed.
  //
  TValue* search(TKey key){
    NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return &cur->Value;
      }

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    } 

    // if get here, not found
    return nullptr;
  }
  
  //starts the recursive distance function
  int distance(int val1, int val2){
	  NODE* cur = Root;
	  if(cur == nullptr){
		  return -1;
	  }
	  int count = -1;
	  
	  if(cur->Key == val1){
		  cout << "in" << endl;
		  count = _distanceFromCur(cur, val2, 0);
	  }else if(cur->Key == val2){
		   cout << "in" << endl;
		  count = _distanceFromCur(cur, val1, 0);
	  }else if(val1 < cur->Key && val2 > cur->Key){
		  count = _distanceOposite(cur, val1, val2);
	  }else if(val2 < cur->Key && val1 > cur->Key){
		  count = _distanceOposite(cur, val2, val1);
	  }else if(val1 < cur->Key && val2 < cur->Key){
		  count = _distance(cur->Left, val1, val2);
	  }else if(val1 > cur->Key && val2 > cur->Key){
		  count = _distance(cur->Right, val1, val2);
	  }
	  return count;
  }


  //
  // insert
  //
  // Inserts the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  //
  void insert(TKey key, TValue value)
	  {
		NODE* prev = nullptr;
		NODE* cur = Root;
		stack<NODE*> nodes;
		while (cur != nullptr){
		  if (key == cur->Key)  // already in tree
			return;

		  nodes.push(cur);  // stack so we can return later:

		  if (key < cur->Key)  // search left:
		  {
			cout<<cur->Key<<endl;
			prev = cur;
			cur = cur->Left;
		  }
		  else
		  {
			prev = cur;
			cur = cur->Right;
		  }
		}
		NODE* newNode;
		newNode = new NODE();
		newNode->Key = key;
		newNode->Value = value;
		newNode->Height = 0;  // leaf node -> sub-tree of height 0:
		newNode->Left = nullptr;
		newNode->Right = nullptr;

		if (prev == nullptr)
		  Root = newNode;
		else if (key < prev->Key)
		  prev->Left = newNode;
		else
		  prev->Right = newNode;
		Size++;
		NODE* Parent;
		while(!nodes.empty()){
			cur = nodes.top();
			nodes.pop();
			if(nodes.empty()){
				Parent = nullptr;
			}else{
				Parent = nodes.top();
			}
			updateHeights(cur);
			_RotateToFix(Parent, cur);
		}
	}


  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder(){
    cout << "Inorder: ";
    _inorder(Root);
    cout << endl;
  }

    void clear(){
    //
    // Re-initialize root pointer and size to "empty":
    //
    _destruct(Root);
    Root = nullptr;
    Size = 0;
    //
    // Intentional pointer error:
    //
  }
  // returns in order
  vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  }
  vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  }
  vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  }
};

