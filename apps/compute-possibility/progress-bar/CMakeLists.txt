# CMake file for building the progress bar

add_library(ProgressBar progress-bar.cpp)

# Travis CI (trusty, g++) complains about `shared_ptr`
# not defined. It's probably because I have forgotten to
# explicitly ask for C++ 11 standard.
target_compile_features(ProgressBar PUBLIC cxx_std_11)
