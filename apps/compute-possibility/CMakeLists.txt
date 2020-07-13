# Build the compute-possibility app

add_executable(compute-possibility compute-possibility.cpp)
target_include_directories(compute-possibility PRIVATE ../../include)
target_compile_features(compute-possibility PRIVATE cxx_std_11)
target_link_libraries(compute-possibility RiskRoll ${GMP} ${GMPXX})
