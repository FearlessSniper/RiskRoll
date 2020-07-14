# RiskRoll

[![Build Status](https://travis-ci.com/FearlessSniper/RiskRoll.svg?branch=master)](https://travis-ci.com/FearlessSniper/RiskRoll)

## Overview
*RiskRoll* is a library written in C++ that aims to compute the possibilities in a *[dice roll]([2])* in a game of *[Risk][1]*.

## Implementation
The possibilities is computed by trying all possible values of the dices. This would result in large runtime when the number of dices is over 3 -- the practical number of dices in game. Large number support with GMP library ([*The GNU Multiple Precision Arithmetic Library*][3]) is added to contain the exponential growth of the number of total possible outcomes. (*Though computing such large number is very unlikely to succeed*)

## Support for each platform

| Operating system | Is supported     |
|------------------|------------------|
| Linux            | Yes              |
| Windows          | Yes (With MinGW) |
|                  |                  |

## Installing GMPlib
The GMP library is a dependency for the RiskRoll project. To install the GMP library:
- Ubuntu:
    ```Shell
    $ apt-get install libgmpdev
    ```
- Arch Linux:
    ```Shell
    $ pacman -S gmp
    ```

## Building the project
This project uses CMake to build. Install CMake before building.
```Shell
$ cmake .
$ cmake --build .
```

[1]: <https://en.wikipedia.org/wiki/Risk_(game)>
[2]: <https://en.wikipedia.org/wiki/Risk_(game)#Gameplay>
[3]: <https://gmplib.org/> "The GNU MP Bignum Library"
