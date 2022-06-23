project(MACE)

file(GLOB_RECURSE MACESimulationGenerator_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACESimulationGenerator STATIC ${MACESimulationGenerator_srcs})
target_link_libraries(MACESimulationGenerator ${Geant4_LIBRARIES})
