#include <iostream>
#include <vector>
#include <string>
#include "vectorData.h"
using namespace std;

/**
 *constructor
 * @param distance distance
 * @param vec vector
 * @param k k
 */
vectorData::vectorData(string vec, string distance, int k) {
    this->vec = vec;
    this->distance = distance;
    this->k = k;
}
/**
 *getter for Distance
 */
string vectorData::getDistance() {
    return this->distance;
}

/**
 *getter for the vector
 */
string vectorData::getVec(){
    return vec;
}

/**
 *getter for the k
 */
int vectorData::getK(){
    return k;
}

/**
 *setter for the distance
 */
void vectorData::setDistance( string distance){
    this->distance=distance;
}

/**
 *setter vector
 */
void vectorData::setVec(string vec){
    this->vec=vec;
}

/**
 *setter for the k
 */
void vectorData::setK(int k){
    this->k=k;
}
