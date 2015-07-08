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


using entry = std::pair< double, std::pair<int,int > >;
//Declare Gillespie class
class Gillepsie{
private:
    double positionX;
    double positionY;
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
    
    
    Gillepsie(std::vector< entry > r)
    : c(r)
    {

        limit = 100;
    }
    
    
    Gillepsie(std::vector< entry > vec, int l)
    : Gillepsie(vec)
    {
        limit = l;
    }
    
    //generates output and puts it in data vector
    void run(){
        COUNT_THIS_SCOPE(__PRETTY_FUNCTION__);

         while(c.getCurrentTime()<limit){
            entry vecPos = c.selectRate();
            switch ( vecPos.second.second )
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
            data.push_back({c.getCurrentTime(),positionX,positionY});
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
    
    Composition getRateStructure(){
        return c;
    }
};



int main() {
    clock_t t;
    std::vector< entry > myRates{{10,{1,1}},{10,{1,2}},{10,{1,3}},{10,{1,4}}};
    Gillepsie myG(myRates, 1000);  
    t = clock();
    std::cout<<"working...";
    myG.run();
    t = clock() - t;
    std::cout<<"finished running in "<<((float)t)/CLOCKS_PER_SEC<<'\n';
    myG.outputData();
    return 0;
}



