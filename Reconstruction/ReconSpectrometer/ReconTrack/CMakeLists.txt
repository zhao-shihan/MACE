project(ReconTrack)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${MPI_CXX_INCLUDE_DIRS})

file(GLOB_RECURSE ReconTrack_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconTrack ${ReconTrack_srcs})
target_link_libraries(ReconTrack DataModel MPITools)

install(TARGETS ReconTrack DESTINATION bin)
