
#ifndef YOAV_ROY_ASS3_REPO_VALIDATIONS_H
#define YOAV_ROY_ASS3_REPO_VALIDATIONS_H

#include <string>
#include "classifiedVector.h"
#include "disVector.h"

using namespace std;

void illegal();

void freeMem(const disVector &currentVec);

bool checkBig(string num, int indexE);

bool checkNumber(string str);

bool checkSpaces(string vec);

vector<double> fillVectorByDelim(const string &strVec, char delim);

vector<classifiedVector> fileToVec(string &file_name);

string getClass(vector<classifiedVector> nearestVecs);

void getUserVec(vector<classifiedVector> &allClassVec,
                const string &distance, int neighborsNum);

bool check_valid_dis(string dis);

bool check_valid_user_input(string userInput);

string getClassification(vector<classifiedVector> &allClassVec,
                         const string &distance, int neighborsNum, string stringVector);

#endif //YOAV_ROY_ASS3_REPO_VALIDATIONS_H
