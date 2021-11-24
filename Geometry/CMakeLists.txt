project(Geometry)

include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB_RECURSE Geometry_SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

add_library(Geometry ${Geometry_SOURCES})
target_link_libraries(Geometry ${Geant4_LIBRARIES})

add_executable(MakeGeometry MakeGeometry.cc)
target_link_libraries(MakeGeometry Geometry ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

install(TARGETS Geometry DESTINATION lib)
install(TARGETS MakeGeometry DESTINATION bin)