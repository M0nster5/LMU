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
// #include "RateStruct.h"
#include "BinaryImplementation.h"


class Gillepsie{
private:
    double currentTime;
    double positionX;
    double positionY;
    double sum;
    int seed;
    int limit;
    BinaryTree bs;
    std::vector< std::vector< double > > data;
    
public:
    Gillepsie(){
        currentTime = 0;
        seed = 0;
        sum = 0;
        limit = 100;
    }
    
    
    Gillepsie(std::vector< std::vector< double > > r)
    : bs(r)
    {
        currentTime = 0;
        seed = 0;
        sum = 0;
        limit = 100;
    }
    
    
    Gillepsie(std::vector< std::vector< double > > vec, int s, int l)
    : Gillepsie(vec)
    {
        seed = s;
        limit = l;
    }
    
    void run(){
        double sum = bs.rSum();
        double place = 0;
        double deltaT = 0;
        std::mt19937 mt_rand;
        mt_rand.seed(seed);
        auto die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
        while(currentTime<limit){
            deltaT = (-log(die()))/sum;
            currentTime+=deltaT;
            place = die()*sum;
            double vecPos = bs.find(place);
            std::cout<< place<<" "<<vecPos<<"\n";
            switch ( (int)vecPos )
            {
                case 1:
                    positionY++;
                    break;
                case 2:
                    positionY--;
                    break;
                case 3:
                    positionX++;
                    break;
                case 4:
                    positionX--;
                    break;
                default:
                    break;
            }
            data.push_back({currentTime,positionX,positionY});
        }
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
    
    BinaryTree getRateStructure(){
        return bs;
    }
};



int main() {
    // insert code here...
    clock_t t;
    std::vector< std::vector< double > > myRates{{1,10},{2,10},{3,10},{4,10}};
    Gillepsie myG(myRates, 8877, 1000);
    t = clock();    
    myG.run();
    t = clock() - t;
    std::cout<<"Finished in "<<((float)t)/CLOCKS_PER_SEC;
    myG.outputData();
    // myG.outputData();
    return 0;
}



