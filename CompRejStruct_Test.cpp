#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include "CompRejStruct.h"

int main(){
	std::vector< std::pair<double,std::pair<int,int> > >myRates{{10,{1,1}},{10,{2,2}},{2,{2,3}}};
	Composition c(myRates);
	c.deleteC(2);
	c.printGroups();
	return 0;
}