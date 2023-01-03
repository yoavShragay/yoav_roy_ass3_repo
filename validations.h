//
// Created by yoav on 1/3/23.
//

#ifndef YOAV_ROY_ASS3_REPO_VALIDATIONS_H
#define YOAV_ROY_ASS3_REPO_VALIDATIONS_H

#include <string>
#include "classifiedVector.h"
#include "disVector.h"

void illegal();
void freeMem(const disVector &currentVec);
bool checkBig(string num, int indexE);
void checkNumber(string str);
void checkSpaces(string vec);
vector<double> fillVectorByDelim(const string &strVec, char delim);
vector<classifiedVector> fileToVec(string &file_name);
string getClass(vector<classifiedVector> nearestVecs);
void getUserVec(vector<classifiedVector> &allClassVec,
                const string &distance, int neighborsNum);
string getClassification(vector<classifiedVector> &allClassVec,const string &distance, int neighborsNum,string stringVector);

#endif //YOAV_ROY_ASS3_REPO_VALIDATIONS_H
