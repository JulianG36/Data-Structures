

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "avl.h"

using namespace std;

int main()
{
  avltree<int, int>  avl;
  int  x;

  cout << "Enter a key to insert into tree (0 to stop)> ";
  cin >> x;

  while (x > 0)
  {
    avl.insert(x, x);
    cout << "Size: " << avl.size() << endl;
    cout << "Height: " << avl.height() << endl;
    avl.inorder();

    cout << endl;
    cout << "Enter a key to insert into tree (0 to stop)> ";
    cin >> x;
  }

  //
  // done:
  //
  return 0;
}
