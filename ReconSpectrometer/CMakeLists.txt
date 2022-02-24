project(ReconSpectrometer)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
# include_directories_recursively(${MACE_THIRD_PARTY_DIR}/GenFit2)
include_directories(${Geant4_INCLUDE_DIRS})

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconSpectrometer ReconSpectrometer.cxx ${sources})
# target_link_libraries(ReconSpectrometer DataModel genfit2)
target_link_libraries(ReconSpectrometer DataModel)

install(TARGETS ReconSpectrometer DESTINATION bin)
