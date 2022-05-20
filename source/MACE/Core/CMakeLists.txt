project(MACE)

file(GLOB_RECURSE MACECore_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACECore ${MACECore_srcs})
target_link_libraries(MACECore ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} yaml-cpp MACEUtility)
