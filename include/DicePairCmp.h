#include "DicePair.h"

namespace RiskRoll {
/*
Warning: As the attacker (a) has a disadvantage when both
dice has the same number, a < b is not necessarily b > a.

Note: A draw is not possible if the number of dice of the
player that has fewer dice is odd.
*/

// Compares two pairs of dice according to the Risk logic.
bool operator<(DicePair& a, DicePair& b);
bool operator>(DicePair& a, DicePair& b);
bool operator==(DicePair& a, DicePair& b);
// Return value: 0: draw; >0: attacker win; <0: defender win
short int cmpDicePair(DicePair& a, DicePair& b);

// Writes a version for DicePair_v as well

// Tell whether the defender wins
bool operator<(DicePair_v& a, DicePair_v& b);
// Tell whether the attacker wins
bool operator>(DicePair_v& a, DicePair_v& b);
// Tell whether it is a draw
bool operator==(DicePair_v& a, DicePair_v& b);
short int cmpDicePair_v(DicePair_v a, DicePair_v b);

}  // namespace RiskRoll