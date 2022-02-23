project(Utility)

include_directories(${MPI_INCLUDE_PATH})

file(GLOB Utility_SOURCES ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Utility ${Utility_SOURCES})
target_link_libraries(Utility ${MPI_LIBRARIES})
