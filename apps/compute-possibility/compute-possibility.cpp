#include <gmpxx.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include "DPPermuGen.h"
#include "DicePair.h"
#include "DicePairCmp.h"
#include "progress-bar/progress-bar.h"

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::flush;
    using namespace RiskRoll;

    struct Player {
        std::string role;
        DicePair_v dp_v;
        std::unique_ptr<DPPermuGen> gen_ptr;
        unsigned short int diceCount;
        mpz_class permutations;
    } attacker, defender;
    struct {
        mpz_class wins, loses, draws;
    } result;
    struct {
        mpf_class win, lose, draw;
    } result_percentage;

    // Array of players so that I can loop through them
    struct Player* players[] = {&attacker, &defender};
    attacker.role = "attacker", defender.role = "defender";
    // Initializing data for attacker and defender
    for (struct Player* player : players) {
        cout << "Please enter the number of dices for the " << player->role
             << ": " << flush;
        cin >> player->diceCount;
        // Create a generator for each players
        player->gen_ptr =
            std::unique_ptr<DPPermuGen>(new DPPermuGen(player->diceCount));
        player->permutations = (*(player->gen_ptr)).count();
    }
    // Moved the line to compute total possibilities above progres bar
    // So that I can get the number of total
    mpz_class totalPossibilities =
        attacker.permutations * defender.permutations;

    // Adding progress bar here
    // Initiallize the ProgressBar
    struct ProgressBar::Details details = {
        std::string("Computing..."), 0, totalPossibilities.get_ui()
    };
    RiskRoll::ProgressBar prog_bar(std::shared_ptr<std::ostream>(&std::cout),
                         std::shared_ptr<struct ProgressBar::Details>(&details));
    prog_bar.update();

    // Test all possibilities and tally the results
    for (DicePair_v atk_dpv : *(attacker.gen_ptr)) {
        for (DicePair_v dfd_dpv : *(defender.gen_ptr)) {
            if (atk_dpv > dfd_dpv)
                result.wins++;
            else if (atk_dpv < dfd_dpv)
                result.loses++;
            else if (atk_dpv == dfd_dpv)
                result.draws++;
            // Refresh the progress bar.
            details.progress++;
            prog_bar.update();
        }
    }
    std::cout << std::endl;

    // Calculate the percentage of wins, loses and draws
    // Turns out it is required to first convert both number to float,
    // then you can get a result with float
    result_percentage.win = static_cast<mpf_class>(result.wins) /
                            static_cast<mpf_class>(totalPossibilities) * 100;
    result_percentage.lose = static_cast<mpf_class>(result.loses) /
                             static_cast<mpf_class>(totalPossibilities) * 100;
    result_percentage.draw = static_cast<mpf_class>(result.draws) /
                             static_cast<mpf_class>(totalPossibilities) * 100;

    // Output the results.
    /*
    The attacker has {} dices.
    The defender has {} dices.
    Therefore there would be {} possibilities.
    The attacker wins {} times ({}%),
    The defender wins {} times ({}%),
    Draws {} times ({}%).
    */
    for (struct Player* player : players) {
        cout << "The " << player->role << " has " << player->diceCount
             << " dices." << endl;
    }
    cout.precision(3);
    cout << "Therefore there would be " << totalPossibilities
         << " possibilities." << endl;
    cout << "The attacker wins " << result.wins << " times ("
         << result_percentage.win << "%)," << endl;
    cout << "The defender wins " << result.loses << " times ("
         << result_percentage.lose << "%)," << endl;
    cout << "Draws " << result.draws << " times. (" << result_percentage.draw
         << "%)." << endl;
}
