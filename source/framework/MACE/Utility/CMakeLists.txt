project(MACE)

file(GLOB_RECURSE MACEUtility_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACEUtility OBJECT ${MACEUtility_srcs})
target_link_libraries(MACEUtility ${MPI_C_LIBRARIES} ${Geant4_LIBRARIES})
