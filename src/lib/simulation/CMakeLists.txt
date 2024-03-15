project(MACE)

file(GLOB_RECURSE MACE_SIMULATION_SRC ${PROJECT_SOURCE_DIR}/MACE/*.c++)

add_library(MACESimulation STATIC ${MACE_SIMULATION_SRC})
target_include_directories(MACESimulation PUBLIC ${MACE_PROJECT_SRC_DIR}/lib/simulation)
target_link_libraries(MACESimulation PUBLIC MACEFramework MACEDataModel MACEDetector)
