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
#include <chrono>

using entry = std::pair< double, std::pair<int,int> >;
//Declare Gillespie class
class Gillepsie{
private:
    bool structIsaBTree{true};
    std::vector< States > creatures;
    std::vector< std::string > rStrings;
    int limit;
    Composition<std::pair<int,int>> c;
    BinaryTree<std::pair<int,int>> bt;
    std::vector<double> timesteps;
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
    Gillepsie(bool s, int numCreatures, std::vector<std::string> states, std::vector< entry > vec,std::vector<double> myIncrements, std::function<double()> d, int l)
    : Gillepsie(s,numCreatures, states, vec, d)
    {
        timesteps = myIncrements;
        limit = l;
    }
    
    //generates output and puts it in data vector
    void run(){
        int currentTimeStep = 0;
        while( ((structIsaBTree) ? bt.getCurrentTime()<limit : c.getCurrentTime()<limit) && ((structIsaBTree) ? bt.getHead()!=nullptr : c.getGroupSums()>0) ){
            entry vecPos = (structIsaBTree) ? bt.find() : c.selectRate();
            creatures[vecPos.second.first-1].increment(vecPos.second.second);

            if (timesteps.size()>0){
                    // std::cout<<"creature "<<x+1<<" position "<<creatures[x].get("positionX")<<"\n";
                while(currentTimeStep<timesteps.size()&&(structIsaBTree)?bt.getCurrentTime()>timesteps[currentTimeStep]:c.getCurrentTime()>timesteps[currentTimeStep]){
                    // std::cout<<"current time: "<<((structIsaBTree)?bt.getCurrentTime():c.getCurrentTime())<<"  currentTimeStep: "<<timesteps[currentTimeStep]<<'\n';
                    data.push_back({timesteps[currentTimeStep],creatures[0].get("positionX")});
                    currentTimeStep++;
                }
            }
            else{
                for (int x = 0; x<creatures.size();x++){

                   // std::cout<<"creature "<<x+1<<" position "<<creatures[x].get("positionX")<<"\n";
                     data.push_back({(structIsaBTree) ? bt.getCurrentTime() : c.getCurrentTime() ,creatures[x].get("positionX")});
                }
            }
        }
        // std::cout<<"final size: "<<creatures.size()<<"\n";
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
    bool getStructIsaBTree(){return structIsaBTree;}
    std::vector<std::vector<double>> getData(){return data;}
    // void outputData(){
    //     const char *path= (structIsaBTree)? "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputBT.txt" : "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputC.txt";
    //     std::ofstream out_data(path);
    //     for (int x = 0; x<data.size();x++){
    //         for ( int y = 0; y<data[0].size();y++){
    //             out_data<<data[x][y]<< ' ';
    //         }
    //         out_data<< '\n';
    //     }
    // }
    
};


int main() {
    std::mt19937 mt_rand;
    mt_rand.seed(98111111228);
    std::function<double()> die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
    
    std::vector<double> seeds;
    clock_t t;
    std::vector<double> inc;
    for (double i = .1; i<4.5;i+=.1){
        inc.push_back(i);
    }
    std::vector< entry > myRates{{10,{1,1}},{10,{1,2}}, {.5,{1,3}}, {.25,{1,4}} };
    Gillepsie myC(false,1,{"positionX"},myRates,inc, die,4);  
    const char *path= (myC.getStructIsaBTree())? "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputBT.txt" : "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputC.txt";;
    std::ofstream out_data(path);
    for (int i = 0; i<1000;i++){
        if(i%100 == 0){
            std::cout<<i/20<<" percent\n";
        }
        myC.run();
        for (int x = 0; x<myC.getData().size();x++){
            for ( int y = 0; y<myC.getData()[0].size();y++){
                out_data<<myC.getData()[x][y]<< ' ';
            }
            out_data<< '\n';
        }
        out_data<<"\n";
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        seeds.push_back(seed);
        mt_rand.seed(seed);
        die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
        myC = Gillepsie(false,1,{"positionX"},myRates, inc, die,4);
    }
    myC = Gillepsie(true,1,{"positionX"},myRates, inc, die,4);
    path= (myC.getStructIsaBTree())? "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputBT.txt" : "/Users/connor/Desktop/C++:Python/GillespieAlgorithm/outputC.txt";;
    out_data = std::ofstream(path);
    for (int i = 0; i<1000;i++){
        if(i%100 == 0){
            std::cout<<50+ i/20<<" percent\n";
        }
        myC.run();
        for (int x = 0; x<myC.getData().size();x++){
            for ( int y = 0; y<myC.getData()[0].size();y++){
                out_data<<myC.getData()[x][y]<< ' ';
            }
            out_data<< '\n';
        }
        out_data<<"\n";
        mt_rand.seed(seeds[i]);
        die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
        myC = Gillepsie(false,1,{"positionX"},myRates, inc, die,4);
    }
   // std::cout<<"finished running in "<<((float)t)/CLOCKS_PER_SEC<<'\n';
    return 0;
}



