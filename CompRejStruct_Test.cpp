#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include "CompRejStruct.h"

int main(){
	std::vector< std::pair<double,double> > myRates{{1,10},{2,10},{3,10},{4,10},{5,100}};
	Composition c(myRates);
	c.printGroups();
	for (int i = 0; i<10;i++){
		std::pair<double, double> random = c.selectRate();
		std::cout<< random.first<<" "<<random.second;
	}


	return 0;
}