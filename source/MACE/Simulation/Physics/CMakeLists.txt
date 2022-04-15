project(Physics)

file(GLOB_RECURSE Physics_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Physics ${Physics_srcs})
target_link_libraries(Physics ${Geant4_LIBRARIES} Core Utility)
