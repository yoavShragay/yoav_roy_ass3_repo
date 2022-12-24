#include "vecComparator.h"

using namespace std;
/**
 * comparator for the min heap
 * @param v1 first vector
 * @param v2 second vector
 * @return true if v1 bigger thn v2, false otherwise
 */
bool vecComparator::operator()(const classifiedVector &v1,
                               const classifiedVector &v2) {
    return v1.getDistance() > v2.getDistance();
}