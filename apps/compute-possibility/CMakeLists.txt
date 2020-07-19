# Build the compute-possibility app

add_subdirectory(progress-bar)
add_executable(compute-possibility compute-possibility.cpp)
target_include_directories(compute-possibility PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(compute-possibility PRIVATE cxx_std_11 cxx_range_for)
target_link_libraries(compute-possibility
    RiskRoll ProgressBar ${GMP} ${GMPXX})
