project(Geometry)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${Geant4_INCLUDE_DIRS})

file(GLOB_RECURSE Geometry_SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

add_library(Geometry ${Geometry_SOURCES})
target_link_libraries(Geometry ${ROOT_LIBRARIES})

add_executable(MakeGeometry MakeGeometry.cc)
target_link_libraries(MakeGeometry Geometry ${ROOT_LIBRARIES})

install(TARGETS Geometry DESTINATION lib)