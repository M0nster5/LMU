#include <vector>
#include <algorithm>
#include <iostream>
#include "BinaryImplementation.h"


int main(){
	std::vector< std::vector< double > > test = {{1,1},{2,2},{3,3},{4,4},{5,5}};
	BinaryTree bs(test);
	std::cout<<bs.find(2);
	// Node* head = bs.getHead();
	return 0;
}
