//  main.cpp
//  Gillespie
//
//  Created by Connor on 29/06/15.
//  Copyright (c) 2015 Connor. All rights reserved.
//

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdio.h>

class RateStructure{
private:
    std::vector< std::vector< double > > rateMap;
    std::vector<double> cummulativeRates;
    double rSum;
public:
    RateStructure(){
        rSum=0;
    }
    RateStructure(std::vector< std::vector< double > > r){
        rateMap = r;
        std::sort(rateMap.begin(),rateMap.end(), [](std::vector< double > r1, std::vector< double > r2){ return r1[1] > r2[1]; });
        // I couldn't find how to make this more efficient
        double sum = 0;
        cummulativeRates.resize(rateMap.size());
        for (int i = 0; i<rateMap.size();i++){
            sum+=rateMap[i][1];
            cummulativeRates[i] = sum;
        }
        rSum=sum;
    }
    
    double find(double place){
        for (int i = 0; i < cummulativeRates.size();i++){
            if (place<cummulativeRates[i])
                return rateMap[i][0];
        }
        return -1;
    }
    double getRSum(){return rSum;}
    
    void printRateMap(){
        for (int x = 0; x < rateMap.size();x++){
            for (int y = 0; y < rateMap[x].size();y++){
                std::cout<<rateMap[x][y]<<" ";
            }
            std::cout<<"\n";
        }
    }
    void printCummulativeRates(){
        for (int x = 0; x<cummulativeRates.size();x++){
            std::cout<<cummulativeRates[x]<<" ";
        }
        std::cout<<"\n";
    }
};


class Gillepsie{
private:
    double currentTime;
    double positionX;
    double positionY;
    double sum;
    int seed;
    int limit;
    RateStructure rs;
    std::vector< std::vector< double > > data;
    
public:
    Gillepsie(){
        currentTime = 0;
        seed = 0;
        sum = 0;
        limit = 100;
    }
    
    
    Gillepsie(std::vector< std::vector< double > > r)
    : rs(r)
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
        double sum = rs.getRSum();
        double place = 0;
        double deltaT = 0;
        std::mt19937 mt_rand;
        mt_rand.seed(seed);
        auto die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
        while(currentTime<limit){
            deltaT = (-log(die()))/sum;
            currentTime+=deltaT;
            place = die()*sum;
            double vecPos = rs.find(place);
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
        // for (double i = 0; i<cummlativeRates.size();i++){
        //     if (place<cummlativeRates[i]){
        //         if (i==1)
        //             position=position+1;
        //         else
        //             position=position-1;
        //         data.push_back({currentTime,i,position});
        //         break;
        //     }
        // }
    }
    
    
    // void printCRates(){
    //     for (int i = 0; i<rates.size();i++){
    //         std::cout<<cummlativeRates[i] << '\t';
    //     }
    // }
    
    // void printRates(){
    //     for (int i = 0; i<rates.size();i++){
    //         std::cout<<rates[i] << '\t';
    //     }
    // }
    
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
    
    RateStructure getRateStructure(){
        return rs;
    }
};



int main() {
    // insert code here...
    std::vector< std::vector< double > > myRates{{1,10},{2,10},{3,10},{4,10}};
    Gillepsie myG(myRates, 8877, 100);
    myG.getRateStructure().printCummulativeRates();    
    myG.run();
    myG.outputData();
    // myG.outputData();
    return 0;
}



