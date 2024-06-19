file(GLOB_RECURSE MACE_SIMULATION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/MACE/*.c++)

add_library(MACESimulation STATIC ${MACE_SIMULATION_SRC})
target_include_directories(MACESimulation PUBLIC ${PROJECT_SOURCE_DIR}/lib/simulation)
target_link_libraries(MACESimulation PUBLIC Mustard::Mustard MACEData MACEDetector MACEReconstruction)
