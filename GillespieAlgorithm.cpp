//  main.cpp
//  Gillespie
//
//  Created by Connor on 29/06/15.
//  Copyright (c) 2015 Connor. All rights reserved.
//
#include <time.h>       
#include "counter.hh"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <utility>
#include "BinaryImplementation.h"
#include "States.h"
#include "CompRejStruct.h"

using entry = std::pair< double, std::pair<int,int> >;
//Declare Gillespie class
class Gillepsie{
private:
    bool structIsaBTree{true};
    std::vector< States > creatures;
    std::vector< std::string > rStrings;
    int limit;
    Composition c;
    BinaryTree bt;
    std::vector< std::vector< double > > data;
    
public:

    //initializers
    Gillepsie()
    :bt()
    {
        limit = 100;
    }
    
    
    Gillepsie(bool s,int numCreatures, std::vector<std::string> states, std::vector< entry > r,std::function<double()> d)
    : bt(r,d), c(r,d) , creatures(numCreatures)
    {
        structIsaBTree = s;
        rStrings = states;
        for (int i = 0; i<numCreatures;i++){
            creatures[i].initialize(states);
        }
        limit = 100;
    }
    
    
    Gillepsie(bool s, int numCreatures, std::vector<std::string> states, std::vector< entry > vec, std::function<double()> d, int l)
    : Gillepsie(s,numCreatures, states, vec, d)
    {
        limit = l;
    }
    
    //generates output and puts it in data vector
    void run(){
        while( ((structIsaBTree) ? bt.getCurrentTime()<limit : c.getCurrentTime()<limit) && ((structIsaBTree) ? bt.getHead()!=nullptr : c.getGroupSums()>0) ){
            entry vecPos = (structIsaBTree) ? bt.find() : c.selectRate();
            //std::cout<<vecPos.first<<" "<<vecPos.second.first<<" "<<vecPos.second.second<<"\n";
            if (vecPos.second.second>2){
                if (vecPos.second.second==3){
                    addCreature(creatures[vecPos.second.first-1].get("positionX"));
                    std::vector< entry > nCreature{ {10,{creatures.size(),1}}, {10,{creatures.size(),2}}, {1,{creatures.size(),3}},{.25,{creatures.size(),4}} };
                    for (int i = 0; i<nCreature.size();i++){
                        (structIsaBTree) ? bt.insert(nCreature[i]) : c.addRate(nCreature[i]);
                    }
                }
                else{
                    (structIsaBTree) ? bt.removeAll(vecPos.second.first,bt.getHead()) : c.deleteC(vecPos.second.first);
                }
            }
            creatures[vecPos.second.first-1].increment(vecPos.second.second);
            for (int x = 0; x<creatures.size();x++){
               // std::cout<<"creature "<<x+1<<" position "<<creatures[x].get("positionX")<<"\n";
                if (creatures[x].get("dead")!=1)
                    data.push_back({(structIsaBTree) ? bt.getCurrentTime() : c.getCurrentTime() ,creatures[x].get("positionX")});
            }
        }
        std::cout<<"final size: "<<creatures.size();
    }
    
    void addCreature(double currentPos){
        States creature;
        creature.initialize(rStrings);
        creature.set(currentPos);
        creatures.push_back(creature);
    }
    void deleteCreature(int index){
        creatures.erase(creatures.begin()+index);
    }

    void outputData(){
        const char *path= (structIsaBTree)? "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputBT.txt" : "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputC.txt";
        std::ofstream out_data(path);
        for (int x = 0; x<data.size();x++){
            for ( int y = 0; y<data[0].size();y++){
                out_data<<data[x][y]<< ' ';
            }
            out_data<< '\n';
        }
    }
    
};


int main() {
    std::mt19937 mt_rand;
    mt_rand.seed(1126199999921);
    std::function<double()> die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);

    clock_t t;
    std::vector< entry > myRates{{10,{1,1}},{10,{1,2}}, {1,{1,3}}, {.25,{1,4}} };
    Gillepsie myG(false,1,{"positionX","dead"},myRates, die ,6);  
    //t = clock();
    //std::cout<<"working...";
    myG.run();
    //t = clock() - t;
    myG.outputData();
    //delete &myG;
    myG =  Gillepsie(true,1,{"positionX","dead"},myRates, die ,1);
    myG.run();
    myG.outputData();
   // std::cout<<"finished running in "<<((float)t)/CLOCKS_PER_SEC<<'\n';
    return 0;
}



