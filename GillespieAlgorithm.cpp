//  main.cpp
//  Gillespie
//
//  Created by Connor on 29/06/15.
//  Copyright (c) 2015 Connor. All rights reserved.
//

#include "counter.hh"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <utility>
#include "CompRejStruct.h"


class Gillepsie{
private:
    double positionX;
    double positionY;
    int limit;
    Composition c;
    std::vector< std::vector< double > > data;
    
public:
    Gillepsie()
    :c()
    {
        limit = 100;
    }
    
    
    Gillepsie(std::vector< std::pair< double,double > > r)
    : c(r)
    {
        limit = 100;
    }
    
    
    Gillepsie(std::vector< std::pair< double,double > > vec, int l)
    : Gillepsie(vec)
    {
        limit = l;
    }
    
    void run(){
         while(c.getCurrentTime()<limit){
            // deltaT = (-log(die()))/sum;
            // currentTime+=deltaT;
            // place = die()*sum;
            // double vecPos = bs.find(place);
            std::pair<double, double> vecPos = c.selectRate();
            switch ( (int)vecPos.first )
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
    // insert code here...
    std::vector< std::pair< double,double > > myRates{{1,10},{2,10},{3,10},{4,10}};
    Gillepsie myG(myRates, 1000);    
    myG.run();
    myG.outputData();
    return 0;
}



