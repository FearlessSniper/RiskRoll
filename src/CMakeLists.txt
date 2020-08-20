# Build the RiskRoll library

set(RISK_ROLL_SOURCES DicePairCmp.cpp DPPermuGen.cpp)

add_library(RiskRoll ${RISK_ROLL_SOURCES})
# Add "/usr/local/include" for installation of gmp by brew
target_include_directories(RiskRoll PUBLIC ${CMAKE_SOURCE_DIR}/include $<$<PLATFORM_ID:Darwin>:/usr/local/include>)
target_compile_features(RiskRoll PRIVATE cxx_std_11)
target_link_libraries(RiskRoll ${GMP} ${GMPXX})
