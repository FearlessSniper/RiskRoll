#include "main.h"

int main(int argc, char** argv) {
    // Loop through all the dice combinations for ? attacker dice and ? defender
    // dice.
    struct resultCount {
        unsigned int attackerWins = 0, defenderWins = 0, draw = 0;
    } n_res;
    struct diceCount {
        unsigned int attackerDice, defenderDice;
    } n_dice;
    struct diceGenerators {
        DiceCombinationGenerator attackerGen, defenderGen;
    };
    const char* msg = "Please enter the number of dice for the ";
    std::cout << msg << "attacker: " << std::flush;
    std::cin >> n_dice.attackerDice;
    std::cout << msg << "defender: " << std::flush;
    std::cin >> n_dice.defenderDice;
    // Warning: Choosing a too much dice may cause an integer overflow.
    // Sticking with 1, 2, 3 won't though
    struct diceGenerators dice_gen {
        DiceCombinationGenerator(n_dice.attackerDice),
            DiceCombinationGenerator(n_dice.defenderDice)
    };
    unsigned int totalOutcomes = dice_gen.attackerGen.totalCombinations() *
                                 dice_gen.defenderGen.totalCombinations();
    std::cout << "There are " << dice_gen.attackerGen.totalCombinations()
              << " and " << dice_gen.defenderGen.totalCombinations()
              << " combinations for the attacker and the defender respectively."
              << std::endl;
    std::cout << "Therefore there would be " << totalOutcomes
              << " possible outcomes." << std::endl;
    std::cout << "Testing outcomes..." << std::endl;
    while (dice_gen.attackerGen.next() != DicePair()) {
        while (dice_gen.defenderGen.next() != DicePair()) {
            DicePair attackerDicePair = dice_gen.attackerGen.getDicePair();
            DicePair defenderDicePair = dice_gen.defenderGen.getDicePair();
            if (attackerDicePair > defenderDicePair) {
                n_res.attackerWins++;
            } else if (attackerDicePair == defenderDicePair) {
                n_res.draw++;
            } else if (attackerDicePair < defenderDicePair) {
                n_res.defenderWins++;
            }
        }
        // Reset the generator for next iteration
        dice_gen.defenderGen = DiceCombinationGenerator(n_dice.defenderDice);
    }
    std::cout << "For case when the attacker have " << n_dice.attackerDice
              << " dices, the defender have " << n_dice.defenderDice
              << " dices," << std::endl;
    std::cout << "The attacker wins " << n_res.attackerWins << " times, ("
              << std::setprecision(4)
              << static_cast<float>(n_res.attackerWins) / totalOutcomes * 100
              << "%)\n"
              << "The defender wins " << n_res.defenderWins << " times, ("
              << static_cast<float>(n_res.defenderWins) / totalOutcomes * 100
              << "%)\n"
              << "Draw " << n_res.draw << " times. ("
              << static_cast<float>(n_res.draw) / totalOutcomes * 100 << "%)";
    return 0;
}

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
    unsigned int cmpSize = std::min(a.size(), b.size());
    short int points = 0;
    DicePair::reverse_iterator it_a = a.rbegin(), it_b = b.rbegin();
    for (unsigned int i = 0; i < cmpSize; i++) {
        if (*it_a > *it_b)
            points++;
        else if (*it_a <= *it_b)
            points--;
        it_a++, it_b++;
    }
    return points;
}

DicePair_v getDiceCombinations(int& ndice) {
    static DicePair_v current;
    if (current.empty()) {
        current.reserve(ndice);
        for (int i = 0; i < ndice; i++)
            current.push_back(1);
    } else {
        DicePair_v::reverse_iterator r_it = current.rbegin();
        while (true) {
            if (r_it == current.rend())
                return DicePair_v();
            if ((*r_it + 1) > 6) {
                r_it++;
            } else {
                (*r_it)++;
                while (r_it != current.rbegin()) {
                    // Copy the current number to the next one
                    *(r_it - 1) = *r_it;
                    r_it--;
                }
                break;
            }
        }
    }
    return current;
}

template <typename T,
          typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
T getNCombinations(T n, T r, bool repetitive) {
    if (repetitive) {
        return factorial(r + n - 1) / (factorial(r) * factorial(n - 1));
    } else
        return factorial(n) / (factorial(r) * factorial(n - r));
}

template <typename T,
          typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
inline T factorial(T n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

DiceCombinationGenerator::DiceCombinationGenerator(unsigned int& ndice) {
    this->current_v.reserve(ndice);
    for (unsigned int i = 0; i < (ndice - 1); i++)
        this->current_v.push_back(1);
    // Set the vector to 1, 1, ... 0 so that the first call to this->next
    // will be 1, 1, ... 1
    this->current_v.push_back(0);
    this->ndice = ndice;
}

inline DicePair DiceCombinationGenerator::getDicePair() {
    return this->updateDicePair();
}

inline DicePair_v DiceCombinationGenerator::getDicePair_v() const {
    return this->current_v;
}

inline unsigned int DiceCombinationGenerator::getDiceNumber() const {
    return this->ndice;
}

DicePair DiceCombinationGenerator::next() {
    this->next_v();
    return this->updateDicePair();
}

DicePair_v DiceCombinationGenerator::next_v() {
    DicePair_v::reverse_iterator r_it = this->current_v.rbegin();
    while (true) {
        if (r_it == this->current_v.rend()) {
            this->current_v = DicePair_v();
            break;
        }
        if ((*r_it + 1) > 6)
            r_it++;
        else {
            (*r_it)++;
            while (r_it != this->current_v.rbegin()) {
                // Copy the current number to the next one
                *(r_it - 1) = *r_it;
                r_it--;
            }
            break;
        }
    }
    return this->current_v;
}

unsigned int DiceCombinationGenerator::totalCombinations() {
    return getNCombinations(static_cast<unsigned int>(6), this->ndice);
}

bool DiceCombinationGenerator::end() {
    return this->current_v.empty();
}

DicePair DiceCombinationGenerator::updateDicePair() {
    this->current.clear();
    for (int i : this->current_v)
        this->current.insert(i);
    return this->current;
}
