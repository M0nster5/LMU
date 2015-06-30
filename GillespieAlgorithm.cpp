//
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

class Gillepsie{
private:
    double currentTime;
    double position;
    double sum;
    int seed;
    int limit;
    std::vector<double> rates;
    std::vector<double> cummlativeRates;

    std::vector< std::vector< double > > data;


public:
    Gillepsie(){
        currentTime = 0;
        seed = 0;
        sum = 0;
        limit = 100;
    }
    
    
    Gillepsie(std::vector<double> vec)
      // : rates(vec),
      //  cummlativeRates(rates.size())

    {
        rates = vec;
        // std::sort(rates.begin(),rates.end(), std::greater<int>());
        std::sort(rates.begin(),rates.end(), [](double r1, double r2){ return r1 > r2; });
        // cummlativeRates.resize(rates.size())
        cummlativeRates = *new std::vector<double>(rates.size());
        std::partial_sum(rates.begin(), rates.end(), cummlativeRates.begin());
        sum = cummlativeRates.back();
    }
    
    
    Gillepsie(std::vector<double> vec, int s, int l)
      : Gillepsie(vec)
    {
        seed = s;
        limit = l;
    }
    
    
    void run(){
        double place = 0;
        double deltaT = 0;
        std::mt19937 mt_rand;
        mt_rand.seed(seed);
        auto die = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);
        while(currentTime<limit){
            deltaT = (-log(die()))/sum;
            currentTime+=deltaT;
            place = die()*sum;
            for (double i = 0; i<cummlativeRates.size();i++){
                if (place<cummlativeRates[i]){
                    if (i==1)
                        position=position+1;
                    else
                        position=position-1;
                    data.push_back({currentTime,i,position});
                    break;
                }
            }
        }
    }

    void printCRates(){
        for (int i = 0; i<rates.size();i++){
            std::cout<<cummlativeRates[i] << '\t';
        }
    }
    
    void printRates(){
        for (int i = 0; i<rates.size();i++){
            std::cout<<rates[i] << '\t';
        }
    }
    
    void outputData(){
        const char *path="/Users/connor/Desktop/C++:Python/Basic Gillespie Algorithm/output.txt";
        std::ofstream out_data(path);
        for (int x = 0; x<data.size();x++){
            for ( int y = 0; y<data[0].size();y++){
                out_data<<data[x][y]<< ' ';
            }
            out_data<< '\n';
        }
    }
    double getSum(){
        return sum;
    }
};


int main() {
    // insert code here...
    std::vector<double> myRates{10,10};
    Gillepsie myG(myRates, 1002, 10000);
    myG.run();
    myG.outputData();
    
   // system("python /Users/connor/Desktop/C++:Python/Basic Gillespie Algorithm/grapher.py");

    return 0;
}

/*git init

git log
git status
git diff
git branch
git commit
git add [-pua]

git stash*/

