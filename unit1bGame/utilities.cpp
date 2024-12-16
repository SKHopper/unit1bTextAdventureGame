#include "utilities.h"

bool randomWeightedBoolean(double weight) {
    return rand() % 1001 / static_cast<double>(1000) >= weight;
}

bool equateBivariateIntegers(bivarInt a, bivarInt b) {
    return (a.x == b.x) && (a.y == b.y);
}

bivarInt sumBivariateIntegers(bivarInt a, bivarInt b) {
    return { a.x + b.x, a.y + b.y };
}

void displayBivariateIntegers(bivarInt integers) {
    cout
        << integers.x
        << ", "
        << integers.y;
}

void clearTerminal() {
    system("cls");
}

bivarInt getDirectionDisplacement(constants::DIRECTION direction) {
    bivarInt displacement{};
    switch (direction) {
    case constants::north:
        displacement = { 0, 1 };
        break;
    case constants::east: 
        displacement = { 1, 0 };
        break;
    case constants::south: 
        displacement = { 0, -1 };
        break;
    case constants::west: 
        displacement = { -1, 0 };
        break;
    default:
        break;
    }
    return displacement;
}

void resetInput() {
    cin.clear();
    cin.ignore(256, '\n');
}
