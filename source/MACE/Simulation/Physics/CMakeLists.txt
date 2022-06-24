project(MACE)

file(GLOB_RECURSE MACESimulationPhysics_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACESimulationPhysics STATIC ${MACESimulationPhysics_srcs})
target_link_libraries(MACESimulationPhysics ${Geant4_LIBRARIES} MACECore MACEUtility)
