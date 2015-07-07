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
#include "CompRejStruct.h"
#include "States.h"

using entry = std::pair< double, std::pair<int,int> >;
//Declare Gillespie class
class Gillepsie{
private:
    std::vector< States > creatures;
    std::vector< std::string > rStrings;
    int limit;
    Composition c;
    std::vector< std::vector< double > > data;
    
public:

    //initializers
    Gillepsie()
    :c()
    {
        limit = 100;
    }
    
    
    Gillepsie(int numCreatures, std::vector<std::string> states, std::vector< entry > r)
    : c(r), creatures(numCreatures)
    {
        rStrings = states;
        for (int i = 0; i<numCreatures;i++){
            creatures[i].initialize(states);
        }
        limit = 100;
    }
    
    
    Gillepsie(int numCreatures, std::vector<std::string> states, std::vector< entry > vec, int l)
    : Gillepsie(numCreatures, states, vec)
    {
        limit = l;
    }
    
    //generates output and puts it in data vector
    void run(){
        std::cout<<"hello";
        while(c.getCurrentTime()<limit){
            //std::cout<<c.getCurrentTime()<<" "<<limit<<std::endl;
            entry vecPos = c.selectRate();
            //std::cout<<vecPos.first<<" "<<vecPos.second.first<<" "<<vecPos.second.second<<"\n";
            if (vecPos.second.second>2){
                if (vecPos.second.second==3){
                    addCreature(creatures[vecPos.second.first-1].get("positionX"));
                    std::vector< entry > nCreature{ {10,{creatures.size(),1}}, {10,{creatures.size(),2}}, {.2,{creatures.size(),3}} };
                    for (int i = 0; i<nCreature.size();i++){
                        c.addRate(nCreature[i]);
                    }
                }
            }
            else
                creatures[vecPos.second.first-1].increment(vecPos.second.second);
            for (int x = 0; x<creatures.size();x++){
               // std::cout<<"creature "<<x+1<<" position "<<creatures[x].get("positionX")<<"\n";
                data.push_back({c.getCurrentTime(),creatures[x].get("positionX")});
            }
        }
    }
    
    void addCreature(double currentPos){
        States creature;
        creature.initialize(rStrings);
        creature.set(currentPos);
        creatures.push_back(creature);
    }

    void outputData(){
        const char *path="/Users/connor/Desktop/C++:Python/GillespieAlgorithm/output.txt";
        std::ofstream out_data(path);
        for (int x = 0; x<data.size();x++){
            for ( int y = 0; y<data[0].size();y++){
                out_data<<data[x][y]<< ' ';
            }
            out_data<< '\n';
        }
    }
    
    Composition getRateStructure(){
        return c;
    }
};



int main() {
    clock_t t;
    std::vector< entry > myRates{{10,{1,1}},{10,{1,2}},{.25,{1,3}}};
    Gillepsie myG(1,{"positionX"},myRates, 4);  
    t = clock();
    std::cout<<"working...";
    myG.run();
    t = clock() - t;
    std::cout<<"finished running in "<<((float)t)/CLOCKS_PER_SEC<<'\n';
    myG.outputData();
    return 0;
}



