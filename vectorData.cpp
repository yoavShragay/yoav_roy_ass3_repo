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
vectorData::vectorData(string vec, string distance, int k) {
    this->vec = vec;
    this->distance = distance;
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
