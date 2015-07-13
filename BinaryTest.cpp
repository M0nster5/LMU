#include <vector>
#include <algorithm>
#include <iostream>
#include "BinaryImplementation.h"
#include <utility>


int main(){
	std::vector< std::pair<double,std::pair<int,int> > > test{{3,{1,1}},{3,{1,2}}};
	BinaryTree bs(test);
	//std::cout<<bs.find(10).second.second;
	int id = 0;
	bs.prettyPrint(bs.getHead(),id);
	bs.insert({19,{1,3}});
	std::cout<<"\n\n";
	// bs.insert({10,{2,1}});
	id = 0;
	bs.prettyPrint(bs.getHead(), id);
	bs.insert({5,{1,3}});
	std::cout<<"\n\n";

	id = 0;
	bs.prettyPrint(bs.getHead(), id);

	// bs.remove(1, bs.getHead());
	// id = 0;
	// bs.insert({7,{2,1}});
	// std::cout<<"\n\n";
	// bs.prettyPrint(bs.getHead(), id);
	std::cout<<"\n\n";
	//bs.remove(2, bs.getHead());	
	// Node* head = bs.getHead();
	return 0;
}
