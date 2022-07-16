project(MACE)

file(GLOB_RECURSE MACECore_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACECore OBJECT ${MACECore_srcs})
target_link_libraries(MACECore MACEEnvironment MACEUtility ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} yaml-cpp Eigen3::Eigen)
