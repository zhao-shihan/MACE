project(ReconSpectrometer)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})

file(GLOB_RECURSE ReconSpectrometer_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconSpectrometer ${ReconSpectrometer_srcs})
target_link_libraries(ReconSpectrometer DataModel)

install(TARGETS ReconSpectrometer DESTINATION bin)
