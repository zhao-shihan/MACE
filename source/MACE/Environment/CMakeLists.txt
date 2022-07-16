project(MACE)

file(GLOB_RECURSE MACEEnvironment_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACEEnvironment OBJECT ${MACEEnvironment_srcs})
target_link_libraries(MACEEnvironment MACEUtility ${MPI_C_LIBRARIES})
