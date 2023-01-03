#include <iostream>
#include <vector>
#include <string>
using namespace std;
class vectorData{
private:
    string distance;
    string vec;
    int k;
public:
    vectorData(string distance,string vec,int k){
        this->distance=distance;
        this->vec=vec;
        this->k=k;
    }
    string getDistance(){
        return distance;
    }
    string getVec(){
        return vec;
    }
    int getK(){
        return k;
    }
    void setDistance( string distance){
        this->distance=distance;
    }
    void setVec(string vec){
        this->vec=vec;
    }
    void setK(int k){
        this->k=k;
    }
};
