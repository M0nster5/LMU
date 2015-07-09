#include <vector>
#include <algorithm>
#include <iostream>
#include "BinaryImplementation.h"
#include <utility>


int main(){
	std::vector< std::pair<double,std::pair<int,int> > > test{{10,{1,1}},{10,{1,2}},{1,{1,3}}, {.25,{1,4}}};
	BinaryTree bs(test);
	int id = 0;
	bs.prettyPrint(bs.getHead(),id);
	std::cout<<"\n\n";
	bs.insert({10,{2,1}});
	id = 0;
	bs.prettyPrint(bs.getHead(), id);
	bs.remove(1, bs.getHead());
	id = 0;
	std::cout<<"\n\n";
	bs.remove(2, bs.getHead());	
	// Node* head = bs.getHead();
	return 0;
}
