#include <gmpxx.h>
#include <iostream>
#include "DPPermuGen.h"

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::flush;
    unsigned short diceCount = 3;
    cout << "Please enter the number of dices: " << flush;
    cin >> diceCount;
    mpz_class nCombinations = RiskRoll::DPPermuGen::count(diceCount);
    cout << "There are " << nCombinations << " combinations for " << diceCount
         << " dices." << endl;
}
