#include <vector>
#include <algorithm>
#include <iostream>

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