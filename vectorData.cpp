#include <iostream>
#include <vector>
#include <string>
#include "vectorData.h"
using namespace std;

/**
 *
 * @param distance
 * @param vec
 * @param k
 */
vectorData::vectorData(string distance,string vec,int k) {
    this->distance = distance;
    this->vec = vec;
    this->k = k;
}
/**
 *
 */
string vectorData::getDistance() {
    return this->distance;
}

/**
 *
 */
string vectorData::getVec(){
    return vec;
}

/**
 *
 */
int vectorData::getK(){
    return k;
}

/**
 *
 */
void vectorData::setDistance( string distance){
    this->distance=distance;
}

/**
 *
 */
void vectorData::setVec(string vec){
    this->vec=vec;
}

/**
 *
 */
void vectorData::setK(int k){
    this->k=k;
}
