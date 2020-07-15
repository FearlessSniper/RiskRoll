# RiskRoll

[![Build Status](https://travis-ci.com/FearlessSniper/RiskRoll.svg?branch=master)](https://travis-ci.com/FearlessSniper/RiskRoll) [![Build Status](https://travis-ci.com/FearlessSniper/RiskRoll.svg?branch=develop)](https://travis-ci.com/FearlessSniper/RiskRoll)

## Overview
*RiskRoll* is a library written in C++ that aims to compute the possibilities in a *[dice roll][2]* in a game of *[Risk][1]*.

## Implementation
The possibilities is computed by trying all possible values of the dices. This would result in large runtime when the number of dices is over 3 -- the practical number of dices in game. Large number support with GMP library ([*The GNU Multiple Precision Arithmetic Library*][3]) is added to contain the exponential growth of the number of total possible outcomes. (*Though computing such large number is very unlikely to succeed*)

## Support for each platform

| Operating system | Is supported     |
|------------------|------------------|
| Linux            | Yes              |
| Windows          | Yes (With MinGW) |
| macOS            | Yes              |

## Installing GMPlib
The GMP library is a dependency for the RiskRoll project. To install the GMP library:
- macOS:
    ```Shell
    $ brew install gmp
    ```
- Ubuntu:
    ```Shell
    $ apt-get install libgmp-dev
    ```
- Arch Linux:
    ```Shell
    $ pacman -S gmp
    ```

## Building the project
This project uses CMake to build. Install CMake before building.
```Shell
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

## Running the project
The build products can be found in the apps folder in build. The **compute-combinations** app computes how many possible outcomes for a given number of dices (6 ^ n). While the **compute-possibility** app tells the probability of winning, losing, or draw in a dice roll.

Example:
```
$ ./compute-combinations
Please enter the number of dices: 3
There are 216 for 3 dices.
```
```
$ ./compute-possibility
Please enter the number of dices for the attacker: 3
Please enter the number of dices for the defender: 2
The attacker has 3 dices.
The defender has 2 dices.
Therefore there would be 7776 possibilities.
The attacker wins 2890 times (37.2%),
The defender wins 2275 times (29.3%),
Draws 2611 times. (33.6%).
```


[1]: <https://en.wikipedia.org/wiki/Risk_(game)>
[2]: <https://en.wikipedia.org/wiki/Risk_(game)#Gameplay>
[3]: <https://gmplib.org/> "The GNU MP Bignum Library"
