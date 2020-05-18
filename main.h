#include <algorithm>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <type_traits>

// Used type_traits in code. Requires C++11

/*
Sidenote: 3 dices: 56 possible combinations
          2 dices: 21 possible combinations
          1 dices: 6  possible combinations
*/

/*
DicePair: Only the maximum n dice is picked, don't care about
the order (combination with repetition), using a multiset with
ascending order.
*/
using DicePair = std::multiset<int, std::less<int> >;
// A variant that implements DicePair with vector for multiple r/w
using DicePair_v = std::vector<int>;

// Compares two pairs of dice according to the Risk logic.
inline bool operator<(DicePair& a, DicePair& b);
inline bool operator>(DicePair& a, DicePair& b);
inline bool operator==(DicePair& a, DicePair& b);
// Return value: 0: draw; >0: attacker win; <0: defender win
short int cmpDicePair(DicePair& a, DicePair& b);
// std::vector<int> testDice(int attackerDice, int defenderDice);
// Gets all possible dice combinations by repeatedly calling this function,
// e.g. getDiceCombinations(2), returns {1, 1}, {1, 2}... and DicePair_v()
// when there is no new combinations
DicePair_v getDiceCombinations(int &ndice);
// A function to get the total number of combinations, in n choose r
// int getNCombinations(int n, int r, bool repetitive = true);
template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
T getNCombinations(T n, T r, bool repetitive = true);
// No built-in factorial function in C++, create a light weight custom one
// inline int factorial(int n);
template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
inline T factorial(T n);
// Converts DicePair_v (vector) to DicePair. Returns a new DicePair.
// std::unique_ptr<DicePair> &toDicePair(DicePair_v &dicePair_v);

class DiceCombinationGenerator {
    public:
        DiceCombinationGenerator(unsigned int &ndice);
        inline DicePair getDicePair();
        inline DicePair_v getDicePair_v() const;
        inline unsigned int getDiceNumber() const;
        DicePair next();
        DicePair_v next_v();
        unsigned int totalCombinations();
        bool end();
    private:
        unsigned int ndice;
        DicePair current;
        DicePair_v current_v;
        DicePair updateDicePair();
};
