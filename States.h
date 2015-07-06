#include <iostream>
#include <utility>
#include <map>
#include <vector>

class Creature{
private:
	std::map<std::string, int> myStates;

public:
	Creature(std::vector<std::string> states){
		for (int i = 0; i<states.size();i++){
			myStates[states[i]]=0;
		}
	}

};