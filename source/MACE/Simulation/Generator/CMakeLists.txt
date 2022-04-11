project(Generator)

file(GLOB_RECURSE Generator_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Generator ${Generator_srcs})
target_link_libraries(Generator ${Geant4_LIBRARIES})
