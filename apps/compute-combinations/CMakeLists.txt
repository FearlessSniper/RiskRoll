# Compile the compute-combinations app

add_executable(compute-combinations compute-combinations.cpp)
target_compile_features(compute-combinations PRIVATE cxx_std_11)
target_link_libraries(compute-combinations RiskRoll ${GMP} ${GMPXX})
