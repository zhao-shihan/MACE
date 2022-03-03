project(Geometry)

include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB_RECURSE Geometry_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Geometry ${Geometry_srcs})
target_link_libraries(Geometry ${Geant4_LIBRARIES})

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry Geometry ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

install(TARGETS MakeGeometry DESTINATION bin)
