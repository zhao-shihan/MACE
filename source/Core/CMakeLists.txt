project(Core)

file(GLOB_RECURSE Core_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Core ${Core_srcs})
target_link_libraries(Core ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} yaml-cpp)
