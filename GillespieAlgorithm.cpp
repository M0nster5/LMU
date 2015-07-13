//  main.cpp
//  Gillespie
//
//  Created by Connor on 29/06/15.
//  Copyright (c) 2015 Connor. All rights reserved.
//compile with g++ -DHAVE_COUNTERS=1 --std=c++11 GillespieAlgorithm.cpp counter.cpp -o GillespieAlgorithm

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
    
    
    Gillepsie(int numCreatures, std::vector<std::string> states, std::vector< entry > r,std::function<double()> die)
    : c(r,die), creatures(numCreatures)
    {
        rStrings = states;
        for (int i = 0; i<numCreatures;i++){
            creatures[i].initialize(states);
        }
        limit = 100;
    }
    
    
    Gillepsie(int numCreatures, std::vector<std::string> states, std::vector< entry > vec, std::function<double()> die, int l)
    : Gillepsie(numCreatures, states, vec, die)
    {
        limit = l;
    }
    
    //generates output and puts it in data vector
    void run(){
        entry errorTest{-1,{-1,-1}};
        while(c.getCurrentTime()<limit&&c.getGroupSums()>0&&rateSize()<3000){
            //std::cout<<"\nsize: "<<creatures.size()<<"\n";
            //c.printGroups();
            //std::cout<<c.getCurrentTime()<<" "<<limit<<std::endl;
            entry vecPos = c.selectRate();
            try{
                if (vecPos == errorTest)
                    throw "selectRate error";
            }catch(const char* msg){
                std::cout<<msg;
            }

            // std::cout<<vecPos.first<<" "<<vecPos.second.first<<" "<<vecPos.second.second<<"\n";
            if (vecPos.second.second>2){
                if (vecPos.second.second==3){
                    addCreature(creatures[vecPos.second.first-1].get("positionX"));
                    std::vector< entry > nCreature{ {10,{creatures.size(),1}}, {10,{creatures.size(),2}}, {1,{creatures.size(),3}},{.25,{creatures.size(),4}} };
                    for (int i = 0; i<nCreature.size();i++){
                        c.addRate(nCreature[i]);
                    }
                }
                else{
                    c.deleteC(vecPos.second.first);
                }
            }
            creatures[vecPos.second.first-1].increment(vecPos.second.second);
            for (int x = 0; x<creatures.size();x++){
               // std::cout<<"creature "<<x+1<<" position "<<creatures[x].get("positionX")<<"\n";
                if (creatures[x].get("dead")!=1)
                    data.push_back({c.getCurrentTime(),creatures[x].get("positionX")});
            }
        }
       // std::cout<<"final size: "<<creatures.size();
    }
    int rateSize(){
        int count = 0;
        for (int i = 0; i<creatures.size();i++){
            if (creatures[i].get("dead")!=1)
                count++;
        }
        return count*4;        
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
    std::vector< entry > myRates{{10,{1,1}},{10,{1,2}},{1,{1,3}}, {.25,{1,4}} };

    std::mt19937 mt_rand;
    mt_rand.seed(192212299);
    std::function<double()> die = std::bind(std::uniform_real_distribution<double>(0,1),mt_rand);

    Gillepsie myG(1,{"positionX","dead"},myRates, die, 5);  

    t = clock();
    std::cout<<"working...";
    myG.run();
    t = clock() - t;
    std::cout<<"finished running in "<<((float)t)/CLOCKS_PER_SEC<<'\n';
    std::cout<<"rate size: "<<myG.rateSize()<<"\n";
    myG.outputData();
    return 0;
}



