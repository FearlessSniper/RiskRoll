# Build the compute-possibility app

add_executable(compute-possibility compute-possibility.cpp)
target_compile_features(compute-possibility PRIVATE cxx_std_11)
