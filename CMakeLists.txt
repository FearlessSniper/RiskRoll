cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RiskRoll
        VERSION 1.0.0
        DESCRIPTION "A simple program computing the probabilities of \
        winning, losing, or having a draw in a single dice roll."
        LANGUAGES CXX)

add_executable(RiskRoll main.cpp)

target_compile_features(RiskRoll PUBLIC cxx_std_11)
set_target_properties(RiskRoll PROPERTIES CXX_EXTENSIONS OFF)