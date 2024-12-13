#include "utilities.h"

bool randomWeightedBoolean(double weight) {
    return rand() % 1001 / static_cast<double>(1000) >= weight;
}
