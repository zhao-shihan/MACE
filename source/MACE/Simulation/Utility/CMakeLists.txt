project(MACE)

# sources
file(GLOB_RECURSE MACESimulationUtility_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

# target
add_library(MACESimulationUtility ${MACESimulationUtility_srcs})
target_link_libraries(MACESimulationUtility ${Geant4_LIBRARIES} ${MPI_C_LIBRARIES})
