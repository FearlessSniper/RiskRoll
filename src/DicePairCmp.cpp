#include "DicePairCmp.h"
#include <algorithm>

namespace RiskRoll {
// Tells whether the defender wins
inline bool operator<(DicePair& a, DicePair& b) {
    return cmpDicePair(a, b) < 0;
}

// Tells whether the attacker wins
inline bool operator>(DicePair& a, DicePair& b) {
    return cmpDicePair(a, b) > 0;
}

// Tells whether it is a draw
inline bool operator==(DicePair& a, DicePair& b) {
    return cmpDicePair(a, b) == 0;
}

// Return value: 0: draw; >0: attacker win; <0: defender win
short int cmpDicePair(DicePair& a, DicePair& b) {
    // unsigned int cmpSize = std::min(a.size(), b.size());
    short int points = 0;
    DicePair::reverse_iterator it_ra = a.rbegin(), it_rb = b.rbegin();
    // for (unsigned int i = 0; i < cmpSize; i++) {
    // if (*it_ra > *it_rb)
    //     points++;
    // else if (*it_ra <= *it_rb)
    //     points--;
    // it_ra++, it_rb++;
    // }
    while (!(it_ra == a.rend() || it_rb == b.rend())) {
        if (*it_ra > *it_rb)
            points++;
        else if (*it_ra <= *it_rb)
            points--;
        it_ra++, it_rb++;
    }
    return points;
}

/*
A recursive implementation of cmpDicePair_v, by taking their max element,
compare it, then remove it, and compare the remaining ones.
*/
// short int cmpDicePair_v(DicePair_v a, DicePair_v b) {
//     DicePair_v::iterator it_max_a = std::max_element(a.begin(), a.end()),
//                          it_max_b = std::max_element(b.begin(), b.end());
//     short int points;
//     if (*it_max_a > *it_max_b) points++;
//     else if (*it_max_a <= *it_max_b) points--;
//     a.erase(it_max_a);
//     b.erase(it_max_b);
//     if (a.empty() || b.empty()) return points;
//     else return points + cmpDicePair_v(a, b);
// }

// Tell whether the defender wins
// inline bool operator<(DicePair_v& a, DicePair_v& b) {
bool operator<(DicePair_v& a, DicePair_v& b) {
    return cmpDicePair_v(a, b) < 0;
}

// Tell whether the attacker wins
// inline bool operator>(DicePair_v& a, DicePair_v& b) {
bool operator>(DicePair_v& a, DicePair_v& b) {
    return cmpDicePair_v(a, b) > 0;
}

// Tell whether it is a draw
// inline bool operator==(DicePair_v& a, DicePair_v& b) {
bool operator==(DicePair_v& a, DicePair_v& b) {
    return cmpDicePair_v(a, b) == 0;
}

/*
This one sorts the dice pair, then compares it and tallys the marks
in desending order.
*/
short int cmpDicePair_v(DicePair_v a, DicePair_v b) {
    // std::sort sorts elements in asending order by default
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    auto r_it_a = a.rbegin(), r_it_b = b.rbegin(), r_it_a_end = a.rend(),
         r_it_b_end = b.rend();
    short int points = 0;
    for (; r_it_a != r_it_a_end && r_it_b != r_it_b_end; r_it_a++, r_it_b++) {
        if (*r_it_a > *r_it_b)
            points++;
        else if (*r_it_a <= *r_it_b)
            points--;
    }
    return points;
}

}  // namespace RiskRoll