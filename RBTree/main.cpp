#include <iostream>
#include <string>
#include "RBTree.h"


int main()
{
	RBTree<int> rb;
	for (int i = 1; i <= 600000; i++) {
		RbNode<int>* tmp = new RbNode<int>;
		tmp->key = i;
		rb.Insert(tmp);
	}
	for (int i = 60000; i >= 1; i--) {
		RbNode<int>* tmp = rb.Delete(i);
		std::cout << tmp->key << " ";
	}
	return 0;
 }