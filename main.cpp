#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "distances.h"
#include "disVector.h"
#include "classifiedVector.h"
#include "vectorsDataStruct.h"

using namespace std;

/**
 * Exit the program in case of an error
 */
void illegal() {
    cout << "Illegal input";
    exit(1);
}

/**
 * This function frees the memory allocated in disVector object.
 * @param currentVec - disVector object that holds distanceAlgo objects.
 */
void freeMem(const disVector &currentVec) {
    for (auto &element: currentVec.getDistances()) {
        delete element;
    }
}

/**
 * checking if the number have e\E in it
 * @param num the number that going to be checked
 * @param indexE the index where the e is
 * @return true if its a number and false if isn't
 */
bool checkBig(string num, int indexE) {
    int num_len = num.length();
    if (indexE != 0 && indexE < num_len - 2) {
        if (num[indexE + 1] == '+' || num[indexE + 1] == '-') {
            return true;
        }
    }
    return false;
}

/**
 * Checking if the string given is a proper number.
 * @param str the number
 */
void checkNumber(string str) {
    bool pointFlag = true;
    int strLen = str.length();
    // case - only "." or only "-" or "." at the end or word to long
    if (str == "." || str == "-" || str[str.length() - 1] == '.'
        || str.length() >= 300) {
        illegal();
    }
    for (int i = 0; i < strLen; i++) {
        // case - more than one point
        if (str[i] == '.') {
            if (!pointFlag) {
                illegal();
            }
            pointFlag = false;
        } else if (i == 0 && str[i] == '-') {
            continue;
        }
            // case - the character isn't a number
        else if (!(isdigit(str[i]))) {
            // case - the number is big
            if (!checkBig(str, i)) {
                illegal();
            }
            i++;
        }
    }
}

/**
 * checking if the spaces between the numbers are in the correct format
 * @param v the string given from the user
 */
void checkSpaces(string vec) {

    if (vec.empty()) {
        illegal();
    }
    for (int i = 0; i < vec.length(); i++) {
        if (vec[i] == ' ') {
            // case - " " at the beginning
            if (i == 0) { illegal(); }
            // case - too many " "
            if (vec[i - 1] == ' ') { illegal(); }
            // case - " " at the end
            if (i == vec.length() - 1) { illegal(); }
        }
    }
}

/**
  * Getting the string from the file, filling a vector with the values
 * in the string, and returning that vector
 * @param strVec - the string given from the user represents a vector
 * @param delim - a char that separates the values in the given string
 * @return a new vector with the values that was in the excel
*/
vector<double> fillVectorByDelim(const string &strVec, char delim) {
    string value;
    vector<double> newVec;
    checkSpaces(strVec);
    stringstream str(strVec);
    while (getline(str, value, delim)) {
        checkNumber(value);
        newVec.push_back(stod(value));
    }
    return newVec;
}

/**
 * Creating a vector of classified vectors, where each
 * classified vector is a single row in the file
 * @param file_name
 * @return - a single vector that contains all the classified vectors
 */
vector<classifiedVector> fileToVec(string &file_name) {
    vector<classifiedVector> allClassVec;
    vector<double> rowVec;
    string line, word;

    fstream file(file_name, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            int index = line.find_last_of(',');
            string cls = line.substr(index + 1, line.length() - 1);
            // create a classification vector for each row
            // and push them into a vector of classified vectors.
            rowVec = fillVectorByDelim(
                    line.substr(0, index), ',');
            classifiedVector classVec(rowVec, cls, rowVec.size());
            // check if the vectors in the file have the same size
            if (!allClassVec.empty() && (classVec.getLen() !=
                                         allClassVec[allClassVec.size() - 1].getLen())) {
                illegal();
            }
            allClassVec.push_back(classVec);
        }
    } else {
        illegal();
    }
    return allClassVec;
}

/**
 * Creating a map 'clsCounts' that contains classification for 'key'
 * and the number of times it appears in the nearestVecs vector for 'value'
 * @param nearestVecs - vector of k nearest vectors
 * @return the most common classification of the k nearest vectors
 */
string getClass(vector<classifiedVector> nearestVecs) {
    map<string, int> clsCounts;
    int maxVal = 0;
    string cls;
    // running over the k nearest classified vectors in nearestVecs
    // clsVec represents a classified vector
    for (auto &clsVec: nearestVecs) {
        // if the key isn't in the map, add the key with value = 1
        if (clsCounts.count(clsVec.getClass()) == 0) {
            clsCounts.insert({clsVec.getClass(), 1});
        }
        // else - increment the value for this key
        clsCounts[clsVec.getClass()]++;
        if (clsCounts[clsVec.getClass()] > maxVal) {
            // remember the most common classification
            maxVal = clsCounts[clsVec.getClass()];
            cls = clsVec.getClass();
        }
    }
    return cls;
}

/**
 * Getting input from user and printing the classification
 * depends on the k nearest vectors
 * The program end when the user write 'EXIT'
 * @param allClassVec - vector that contains all classified vectors
 * @param distance - string that represents the distance function
 * @param neighborsNum - number of neighbors to check from
 */
void getUserVec(vector<classifiedVector> &allClassVec,
                const string &distance, int neighborsNum) {
    while (true) {
        string stringVector;
        getline(cin, stringVector);
        if (stringVector == "EXIT") {
            break;
        }
        // Convert from string vector to double vector
        vector<double> newVec = fillVectorByDelim(stringVector, ' ');
        // Check if the input vector is the same length as the file vectors
        if (newVec.size() != allClassVec[0].getLen()) {
            illegal();
        }
        disVector currentVec(newVec, distance);
        vectorsDataStruct dataStr(currentVec, allClassVec);
        vector<classifiedVector> k_nearest = dataStr.getK(neighborsNum);
        cout << getClass(k_nearest) << endl;
        // free the memory we allocated
        freeMem(currentVec);
    }
}

/**
 * checking the correctness of the values given at compilation
 * @param argv the array of values given at compilation
 */
void checkArgv(char *argv[]) {
    bool flag = false;
    double num;
    checkNumber(argv[1]);
    //check if the number is natural
    num = stod(argv[1]);
    if ((floor(num) != ceil(num)) || num < 1) {
        illegal();
    }
    vector<string> distances = {"AUC", "MAN", "CHB", "CAN", "MIN"};
    for (auto &distance: distances) {
        if (argv[3] == distance) {
            flag = true;
        }
    }
    if (!flag) {
        illegal();
    }
}

//// This is the main function
int main(int argc, char *argv[]) {
    string distance, file_name;

    // accepting from user input
    checkArgv(argv);
    int neighborsNum = stoi(argv[1]);
    file_name = argv[2];
    distance = argv[3];

    // Put each line in the file into a vector that contains string vectors
    // One string vector represents one line in the file
    vector<classifiedVector> allClassVec = fileToVec(file_name);

    // Print the k closest neighbors to the input vector
    getUserVec(allClassVec, distance, neighborsNum);
    return 0;
}
