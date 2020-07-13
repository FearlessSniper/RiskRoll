# Build the RiskRoll library

set(RISK_ROLL_SOURCES DicePairCmp.cpp DPPermuGen.cpp)

add_library(RiskRoll ${RISK_ROLL_SOURCES})
target_include_directories(RiskRoll PUBLIC ../include)
target_compile_features(RiskRoll PRIVATE cxx_std_11)
target_link_libraries(RiskRoll ${GMP} ${GMPXX})
