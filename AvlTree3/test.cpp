/*test.cpp*/

#include <iostream>
#include <vector>

#include "avl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) empty tree") 
{
  avltree<int, int>  avl;
  int distance = avl.distance(20,10);
  REQUIRE(distance == -1);
  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
}
TEST_CASE("(2) AVL tree with 4 nodes") 
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 4 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);
  avl.insert(125, -125);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 4);
  REQUIRE(avl.height() == 2);

  REQUIRE(keys[0] == 50);
  REQUIRE(values[0] == -50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(values[1] == -100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(values[2] == -125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(values[3] == -150);
  REQUIRE(heights[3] == 1);
}

TEST_CASE("(3) empty tree") 
{
  avltree<int, int>  avl;

  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
}

TEST_CASE("(4) just one node") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 10);
	avl.insert(126, 10);
	int distance  = avl.distance(120,121);
	

  REQUIRE(avl.size() == 2);
  REQUIRE(avl.height() == 1);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
  REQUIRE(distance == -1);

	
}
TEST_CASE("(5) insert left Single Right Rotate Root"){
	avltree<int, int>  avl;
	
		avl.insert(20, -20);
		avl.insert(19, -19);
		avl.insert(18, -18);
		avl.insert(17, -17);
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size() == 4);
	vector<int>  keys, values, heights;
	  keys = avl.inorder_keys();
	  values = avl.inorder_values();
	  heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 17);
	REQUIRE(keys[1] == 18);
	REQUIRE(keys[2] == 19);
	REQUIRE(keys[3] == 20);
	
	REQUIRE(values[0] == -17);
	REQUIRE(values[1] == -18);
	REQUIRE(values[2] == -19);
	REQUIRE(values[3] == -20);

	
	
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 2);
	REQUIRE(heights[3] == 0);
}
	
TEST_CASE("(6) insert right Single Left Rotate Root"){
	avltree<int, int>  avl;
	
	avl.insert(18, -18);
	avl.insert(19, -19);
	avl.insert(20, -20);
	avl.insert(21, -21);
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size() == 4);
	vector<int>  keys, values, heights;
	  keys = avl.inorder_keys();
	  values = avl.inorder_values();
	  heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 18);
	REQUIRE(keys[1] == 19);
	REQUIRE(keys[2] == 20);
	REQUIRE(keys[3] == 21);
	
	
	REQUIRE(values[0] == -18);
	REQUIRE(values[1] == -19);
	REQUIRE(values[2] == -20);
	REQUIRE(values[3] == -21);
	
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 2);
	REQUIRE(heights[2] == 1);
	REQUIRE(heights[3] == 0);
	
}
	
TEST_CASE("(7) insert left double rotate outside"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(15, -15);
	avl.insert(5, -5);
	avl.insert(17, -17);
	avl.insert(16, -16);
	
	
	REQUIRE(avl.height() == 3);
	REQUIRE(avl.size() == 7);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 3);
	REQUIRE(heights[3] == 0);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 2);
	REQUIRE(heights[6] == 0);
	
}

TEST_CASE("(8) insert left double rotate inside"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(15, -15);
	avl.insert(5, -5);
	avl.insert(13, -13);
	avl.insert(16, -16);
	avl.insert(18, -18);
	avl.insert(35, -35);
	
	int distance = avl.distance(12, 10);
	REQUIRE(distance == -1);
	REQUIRE(avl.height() == 3);
	REQUIRE(avl.size() == 9);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	
// 	REQUIRE(heights[0] == 0);
// 	REQUIRE(heights[1] == 1);
// 	REQUIRE(heights[2] == 0);
// 	REQUIRE(heights[3] == 2);
// 	REQUIRE(heights[4] == 0);
// 	REQUIRE(heights[5] == 1);
// 	REQUIRE(heights[6] == 0);
}
TEST_CASE("(9) insert right double rotate inside"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(35, -35);
	avl.insert(25, -25);
	avl.insert(12, -12);
	avl.insert(22, -22);
	avl.insert(27, -27);
	avl.insert(28, -28);
	
	
	
	REQUIRE(avl.height() == 3);
	REQUIRE(avl.size() == 9);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	
	REQUIRE(heights[0] == 1);
	REQUIRE(heights[1] == 0);
	REQUIRE(heights[2] == 3);
	REQUIRE(heights[3] == 0);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 2);
	REQUIRE(heights[6] == 0);
	REQUIRE(heights[7] == 1);
	REQUIRE(heights[8] == 0);
	REQUIRE(heights[9] == 0);
	
}

TEST_CASE("(10) insert right double rotate outside"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(35, -35);
	avl.insert(25, -25);
	avl.insert(12, -12);
	avl.insert(22, -22);
	avl.insert(27, -27);
	avl.insert(26, -26);
	
	REQUIRE(avl.height() == 3);
	REQUIRE(avl.size() == 9);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	
	REQUIRE(heights[0] == 1);
	REQUIRE(heights[1] == 0);
	REQUIRE(heights[2] == 3);
	REQUIRE(heights[3] == 0);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 0);
	REQUIRE(heights[6] == 2);
	REQUIRE(heights[7] == 1);
	REQUIRE(heights[8] == 0);
	REQUIRE(heights[9] == 0);
}
TEST_CASE("(11) insert right rotate subtree"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(25, -25);
	avl.insert(12, -12);
	avl.insert(22, -22);

	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size() == 6);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	
	REQUIRE(heights[0] == 1);
	REQUIRE(heights[1] == 0);
	REQUIRE(heights[2] == 2);
	REQUIRE(heights[3] == 0);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 0);

}
TEST_CASE("(13) insert left rotate subtree"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(12, -12);
	avl.insert(35, -35);
	avl.insert(40, -40);
	

	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size() == 6);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	
	REQUIRE(heights[0] == 1);
	REQUIRE(heights[1] == 0);
	REQUIRE(heights[2] == 2);
	REQUIRE(heights[3] == 0);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 0);

}
TEST_CASE("(14) distance Left"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(5, -5);

	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size() == 4);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	int distance = avl.distance(5, 20);
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 2);
	REQUIRE(heights[3] == 0);
	REQUIRE(distance == 2);

}
TEST_CASE("(15) Split Root"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(5, -5);
	avl.insert(40, -40);
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size() == 5);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	int distance = avl.distance(40, 5);
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 2);
	REQUIRE(heights[3] == 1);
	REQUIRE(heights[4] == 0);
	REQUIRE(distance == 4);

}
TEST_CASE("(15) Left Move"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(5, -5);
	avl.insert(40, -40);
	avl.insert(15, -15);
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size() == 6);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	int distance = avl.distance(15, 5);
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 0);
	REQUIRE(heights[3] == 2);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 0);
	
	REQUIRE(distance == 2);

}

TEST_CASE("(16) Combined"){
	avltree<int, int>  avl;
	avl.insert(20, -20);
	avl.insert(10, -10);
	avl.insert(30, -30);
	avl.insert(5, -5);
	avl.insert(40, -40);
	avl.insert(15, -15);
	avl.insert(17, -17);
	
	REQUIRE(avl.height() == 3);
	REQUIRE(avl.size() == 7);
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	int distance = avl.distance(20, 20);
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 2);
	REQUIRE(heights[2] == 1);
	REQUIRE(heights[3] == 0);
	REQUIRE(heights[4] == 3);
	REQUIRE(heights[5] == 1);
	REQUIRE(heights[6] == 0);
	REQUIRE(distance == 0);

}

TEST_CASE("(17) Right Distance"){
	avltree<int, int>  avl;
	avl.insert(10, -10);
	avl.insert(5, -5);
	avl.insert(30, -30);
	avl.insert(20, -20);
	avl.insert(3, -3);
	avl.insert(40, -40);
	avl.insert(50, -50);
	avl.insert(15, -15);
	REQUIRE(avl.height() == 3);
	REQUIRE(avl.size() == 8);
	
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
	values = avl.inorder_values();
	heights = avl.inorder_heights();
	int distance = avl.distance(3, 50);
	REQUIRE(distance == 5);
	
}


	

	
