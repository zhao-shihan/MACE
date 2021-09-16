project(SpectrometerReconstruction)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories_recursively(${MACE_PROJECT_ROOT_DIR}/Buildin/GenFit2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(SpectrometerReconstruction SpectrometerReconstruction.cc ${sources} ${headers})
target_link_libraries(SpectrometerReconstruction genfit2)
