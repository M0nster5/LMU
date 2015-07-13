#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>
#include <random>
#include <chrono>
#include "counter.hh"
// #include <usr/local/Cellar/boost/test/included/unit_test.hpp>


class Group{
private:
	int level{0};
	double gSum{0};
	std::vector< std::pair<double, std::pair<int, int> > > elements;

public:
	Group() = default;
	Group(int l){
		level = l;
	}
	void add(std::pair<double,std::pair<int, int> > p){
		gSum+=p.first;
		elements.push_back(p);
	}
	std::pair<double,std::pair<int, int> > find(double compMin,  std::function<double()> die){
		updateGSum();
		double levelHeight = pow(2,level)*compMin;
        std::pair<double,std::pair<int, int> > current = elements[ceil(die()*(elements.size()-1))];
        double place = die() * levelHeight;
        COUNT_THIS_SCOPE(__PRETTY_FUNCTION__);

        while(current.first<place){
        	Counter::ScopeCounter<> sc("main loop");
            current = elements[ceil(die()*(elements.size()-1))];
        	place = die() * levelHeight;
        }
        return current;
	}
	double getGSum(){return gSum;}


	void printAll(){
		std::cout<<"Level: "<<level<<"\n";
		std::cout<<"Elements in Group: ";
		for (int i = 0; i < elements.size(); i++){
			std::cout<<"Creature num: "<<elements[i].second.first<<"  Action num: "<<elements[i].second.second <<" "<<elements[i].first<<"\t";
		}
		std::cout<<"\n"<<"Group Sum: "<<gSum<<"\n\n";
	}
	bool hasCreature(double identifier){
		return std::find_if(std::begin(elements),std::end(elements),[&](std::pair<double, std::pair<int, int> > element){return element.second.first == identifier;})!=elements.end();
	}

	void remove(int group){
		elements.erase(std::remove_if(elements.begin(),elements.end(),[&](std::pair<double, std::pair<int, int> > element){return element.second.first == group; } ));
	}
	void updateGSum(){
		gSum = 0;
		for (int i = 0; i<elements.size();i++){
			gSum+=elements[i].first;
		}
	}
};



class Composition{
private:
	std::function<double()> die;
	double currentTime{0};
	double deltaT{0};
	std::pair<double,std::pair<int, int> > min{0,{0,0}};
	double groupSums{0};
	std::vector< Group >  groups;
public:
	Composition() = default;
	Composition(std::vector< std::pair<double,std::pair<int, int> > > r,std::function<double()> d){
		die = d;
		min = *std::min_element(std::begin(r),std::end(r),[]( std::pair<double,std::pair<int, int> > r1, std::pair<double,std::pair<int, int> > r2){return r1.first<r2.first;});
		std::cout<<min.first<<"\n";
		Group a(1);
		groups.push_back(a);
		for (int x = 0; x < r.size(); x++){
			for (int y = 0; y < groups.size();y++){
				if (r[x].first<pow(2,y+1)*min.first){
					groups[y].add(r[x]);
					break;
				}
				else if(y == groups.size()-1)
				{
					groups.emplace_back(y+2);
				}
			}
			std::cout<<"----------------------------------\n";
			printGroups();
		}
		for (int i = 0; i<groups.size(); i++){
			groupSums += groups[i].getGSum();
		}
	}
	void printGroups(){
		std::cout<<" groupsSize "<< groups.size()<<"\n\n"<<std::flush;
		for (int i = 0; i<groups.size();i++){
			std::cout<<i<<"\n";  
			groups[i].printAll();
		}
		std::cout<<"\nGroupSums: "<<groupSums<<"\n-------------------------------------------";
	}
	void updateGroupSums(){
		groupSums = 0;		
		for (int i = 0; i<groups.size(); i++){
			groupSums += groups[i].getGSum();
		}
	}

	void addRate(std::pair<double,std::pair<int, int> > p){
		// if (p.first<min.first){
		// 	min = p;
		// }
		for (int y = 0; y < groups.size();y++){
			if (p.first<pow(2,y+1)*min.first){
				groups[y].add(p);
				break;
			}
			else if (y == groups.size()-1)
				groups.emplace_back(y+2);
		}
		updateGroupSums();
	}

	std::pair<double,std::pair<int, int> > selectRate(){
		updateGroupSums();
	    deltaT = (-log(die()))/groupSums;
        currentTime+=deltaT;
        double place = die()*groupSums;
		for (int i = groups.size()-1; i>=0;i--){
			if (place<groups[i].getGSum()){
				return groups[i].find(min.first,die);
			}
			else
				place-=groups[i].getGSum();
		}
		return {-1,{-1,-1}};
	}

	void deleteC(double identifier){
		for (int x = 0; x<groups.size();x++){
			while(groups[x].hasCreature(identifier)){
				groups[x].remove(identifier);
				groups[x].updateGSum();
			}
		}
		updateGroupSums();
	}
	double getGroupSums(){return groupSums;}
	double getCurrentTime(){return currentTime;}
};