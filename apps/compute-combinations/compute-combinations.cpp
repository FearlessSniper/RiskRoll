#include <iostream>
#include <gmpxx.h>
#include "DPPermuGen.h"

int main () {
    using std::cin;
    using std::cout;
    using std::flush;
    using std::endl;
    unsigned short diceCount = 3;
    cout << "Please enter the number of dices: " << flush;
    cin >> diceCount;
    mpz_class nCombinations = RiskRoll::DPPermuGen::count(diceCount);
    cout << "There are " << nCombinations << " for " << diceCount << " dices." << endl;
}
