cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RiskRoll
        VERSION 1.0.0
        DESCRIPTION "A simple program computing the probabilities of \
        winning, losing, or having a draw in a single dice roll."
        LANGUAGES CXX)

include(CMakePrintHelpers)

# Add all warnings for gcc/g++
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Disabled... not good! Use add_compile_options for all targets
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    # cmake_print_variables(CMAKE_CXX_FLAGS)
    add_compile_options(-Wall -Wextra)
endif()

find_library(GMP gmp)
find_library(GMPXX gmpxx)

cmake_print_variables(RiskRoll GMP GMPXX)

add_subdirectory(src)
add_subdirectory(apps/compute-combinations)
add_subdirectory(apps/compute-possibility)
