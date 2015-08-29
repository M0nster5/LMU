#include <iostream>
#include <utility>
#include <map>
#include <vector>

class States{
private:
	std::map<std::string, double> myStates{};

public:
	States() = default;
	States(std::vector<std::string> states){
		for (int i = 0; i<states.size();i++){
			myStates[states[i]]=0;
		}
	}

	void initialize(std::vector<std::string> states){
		for (int i = 0; i<states.size();i++){
			myStates[states[i]]=0;
		}
	}
	void increment(int reference){
		        switch(reference){
                case 1:
                    myStates["positionX"]+=20;
                    break;
                case 2:
                    myStates["positionX"]-=20;
                    break;
                case 4:
                	myStates["dead"]=1;
                	break;
                default:
                    break;
            }
	}
	int size(){return myStates.size();}
	double get(std::string a){
		return myStates.at(a);
	}
	void set(double pX){myStates["positionX"] = pX;}

};