#include "DPPermuGen.h"
#include "DicePair.h"

namespace RiskRoll {
DPPermuGen::DPPermuGen(unsigned short int& diceCount) {
    this->diceCount = diceCount;
}

DPPermuGen::iterator DPPermuGen::begin() const {
    DicePair_v dicePair;
    dicePair.reserve(this->diceCount);
    for (int i = 0; i < this->diceCount; i++) {
        dicePair.push_back(1);
    }
    return DPPermuGen::iterator(dicePair);
}

DPPermuGen::iterator DPPermuGen::end() const {
    // DPPermuGen::iterator::iterator(DicePair_v) is call
    // by reference; have to create a variable before
    // returning.
    // Create empty DicePair_v as end of iteration
    DicePair_v dp_v;
    return DPPermuGen::iterator(dp_v);
}

mpz_class DPPermuGen::count() const {
    return DPPermuGen::count(this->diceCount);
}

mpz_class DPPermuGen::count(const unsigned short int& diceCount) {
    // Algorithm: count = 6 ^ n
    mpz_class count(1);
    // Implement exponential function by repeated multiplication
    for (int i = 0; i < diceCount; i++) {
        count *= 6;
    }
    return count;
}

DPPermuGen::iterator::iterator(DicePair_v& dp_v) {
    this->value = dp_v;
}

DPPermuGen::iterator& DPPermuGen::iterator::operator=(iterator& it) {
    this->value = *it;
    return *this;
}

DicePair_v DPPermuGen::iterator::operator*() const {
    return this->value;
}

DPPermuGen::iterator& DPPermuGen::iterator::operator++() {
    auto r_it = (this->value).rbegin(), r_it_end = (this->value).rend();
    while (true) {
        if (r_it == r_it_end) {
            this->value = DicePair_v();
            break;
        }
        if ((*r_it + 1) > 6) {
            *r_it = 1;
            r_it++;
        } else {
            (*r_it)++;
            break;
        }
    }
    return *this;
}

bool DPPermuGen::iterator::operator!=(iterator& it) const {
    // Are the values of each other unequal?
    return *(*this) != *it;
}

bool DPPermuGen::iterator::operator==(iterator& it) const {
    return *(*this) == *it;
}

}  // namespace RiskRoll