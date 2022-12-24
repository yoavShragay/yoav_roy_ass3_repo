#ifndef _VECCOMPARATOR_H_
#define _VECCOMPARATOR_H_

#include "vectorsDataStruct.h"
#include "disVector.h"
#include "classifiedVector.h"
#include <vector>
#include <string>

class vecComparator {
public:
    bool operator()(const classifiedVector &v1, const classifiedVector &v2);
};

#endif //_VECCOMPARATOR_H_
