project(Geometry)

file(GLOB_RECURSE Geometry_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Geometry ${Geometry_srcs})
target_link_libraries(Geometry ${Geant4_LIBRARIES})

add_subdirectory(Tests)
