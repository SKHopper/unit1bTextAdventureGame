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

string specialNameGenerator(int length){
    string name = "";
    int startShifter = randomInteger(1);

    for (int i = 0; i < length; i++) {
        name.append(
            ((startShifter) ? 1-(i % 2) : (i % 2)) 
            ? constants::SPECIAL_CONSONANTS.at(randomInteger(constants::SPECIAL_CONSONANTS.size() - 1))
            : constants::SPECIAL_VOWELS.at(randomInteger(constants::SPECIAL_VOWELS.size() - 1))
        );
    }

    char start = toupper(name.at(0));
    name.assign(name.begin()+1,name.end());

    return start + name;
}

int linearStringSearch(vector<string> arr, string a) {
    for (int i = 0; i < arr.size(); i++) {
        if (a == arr.at(i)) {
            //index
            return i;
        }
    }

    //fail
    return -1;
}

double getElapsedSecondsResultMultiplier(double elapsedSeconds) {
    if (elapsedSeconds > constants::ALLOWED_INPUT_DELAY_SECONDS) {
        elapsedSeconds = constants::ALLOWED_INPUT_DELAY_SECONDS;
    }
    double enumerator = constants::ALLOWED_INPUT_DELAY_SECONDS - elapsedSeconds;
    double normalized = enumerator / constants::ALLOWED_INPUT_DELAY_SECONDS;
    return  normalized + 0.5;
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

int selectFromOddsTable(vector<bivarInt> table) {
    int oddsSum = 0;
    for (bivarInt& tableElem : table) {
        oddsSum += tableElem.y;
    }
    int selector = rand() % oddsSum;

    oddsSum = 0;
    for (bivarInt& tableElem : table) {
        oddsSum += tableElem.y;
        if (oddsSum >= selector) {
            selector = tableElem.x;
            break;
        }
    }

    return selector;
}

void resetInput() {
    cin.clear();
    cin.ignore(1000, '\n');
}

int randomInteger(int max) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<std::mt19937::result_type> distributor(0, max);
    return distributor(generator);
}