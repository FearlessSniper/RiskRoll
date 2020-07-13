#include <set>
#include <unordered_set>
#include <vector>

namespace RiskRoll {
/*
DicePair: Only the maximum n dice is picked, don't care about
the order (combination with repetition), using a multiset with
ascending order.
Changed data type to unsigned char to save space
*/
using DicePair = std::multiset<unsigned char, std::less<unsigned char> >;

// Best for squential manipulation
using DicePair_v = std::vector<unsigned char>;

// A variant that is also DicePair but is unordered
// Unused: inconvinient for sequential read/write
// using DicePair_unordered = std::unordered_multiset<int>;
// using DicePair_un = DicePair_unordered;

// Can't use std::array as the size of it has to be binded
// at compile time
// template <std::size_t T>
// using DicePair_ary = std::array<int, T>;

}  // namespace RiskRoll
