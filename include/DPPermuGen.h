#include <gmpxx.h>
#include <iterator>
#include "DicePair.h"

namespace RiskRoll {
// Only leave the generator with permutation, a.k.a. 1,1,1 ... 1,2,1

// Generates a list of DicePair in Permutation with repetition
class DPPermuGen {
   public:
    class iterator {
       public:
        iterator(DicePair_v& dp_v);
        iterator& operator=(iterator& it);
        DicePair_v operator*() const;
        iterator& operator++();
        bool operator!=(iterator& it) const;
        bool operator==(iterator& it) const;

       private:
        DicePair_v value;
    };
    DPPermuGen(unsigned short int& diceCount);
    iterator begin() const;
    iterator end() const;
    // The number of DicePair to be generated
    mpz_class count() const;
    static mpz_class count(const unsigned short int& diceCount);

   private:
    unsigned short int diceCount;
};

}  // namespace RiskRoll

// Specializing std::iterator_traits must be done outside the RiskRoll
// namespace as iterator_traits is in std namespace.
template <>
struct std::iterator_traits<RiskRoll::DPPermuGen::iterator> {
    typedef int difference_type;
    typedef RiskRoll::DicePair_v value_type;
    typedef RiskRoll::DicePair_v* pointer;
    typedef RiskRoll::DicePair_v& reference;
    typedef std::forward_iterator_tag iterator_catagory;
};
