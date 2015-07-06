#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>
#include <random>
#include <chrono>



class Group{
private:
	int level{0};
	double gSum{0};
	std::vector< std::pair<double, int> > elements;

public:
	Group(int l){
		level = l;
	}
	void add(std::pair<double,int> p){
		gSum+=p.first;
		elements.push_back(p);
	}
	std::pair<double,int> find(double compMin){
		double levelHeight = pow(2,level)*compMin;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 mt_rand;
		mt_rand.seed(seed);
        auto die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
        auto vecPlace = std::bind(std::uniform_int_distribution<int>(0,elements.size()-1), mt_rand);
        std::pair<double, int> current = elements[vecPlace()];
        double place = die() * levelHeight;
        while(current.first<place){
        	current = elements[vecPlace()];
        	place = die() * levelHeight;
        }
        return current;
	}
	double getGSum(){return gSum;}

	void printAll(){
		std::cout<<"Level: "<<level<<"\n";
		std::cout<<"Elements in Goup: ";
		for (int i = 0; i < elements.size(); i++){
			std::cout<<elements[i].second<<" "<<elements[i].first<<"\t";
		}
		std::cout<<"\n"<<"Group Sum: "<<gSum<<"\n\n";
	}
};



class Composition{
private:
	double currentTime{0};
	double deltaT{0};
	std::pair<double,int> min{0,0};
	double groupSums{0};
	std::vector< Group >  groups;
public:
	Composition() = default;
	Composition(std::vector< std::pair<double,int> > r){
		min = *std::min_element(std::begin(r),std::end(r),[]( std::pair<double,int> r1, std::pair<double,int> r2){return r1.first<r2.first;});
		Group a(1);
		groups.push_back(a);
		for (int x = 0; x < r.size(); x++){
			for (int y = 0; y < groups.size();y++){
				if (r[x].first<pow(2,y+1)*min.first){
					groups[y].add(r[x]);
				}
				else
					groups.push_back(*new Group(y+2));
			}
		}
		for (int i = 0; i<groups.size(); i++){
			groupSums += groups[i].getGSum();
		}
	}
	void printGroups(){
		for (int i = 0; i<groups.size();i++){
			groups[i].printAll();
		}
	}

	Group selectGroup(){
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 mt_rand;
		mt_rand.seed(seed);
		auto die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
	    deltaT = (-log(die()))/groupSums;
        currentTime+=deltaT;
        double place = die()*groupSums;
		for (int i = groups.size()-1; i>=0;i--){
			if (place<groups[i].getGSum()){
				return groups[i];
			}
			else
				place-=groups[i].getGSum();
		}
		return *new Group(0);
	}

	std::pair<double,double> selectRate(){
		return selectGroup().find(min.first);
	}
	double getCurrentTime(){return currentTime;}
};