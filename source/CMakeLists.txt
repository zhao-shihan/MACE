project(MACE)

# Config for MACE
include(${MACE_PROJECT_CMAKE_DIR}/MACECompileOptions.cmake)

# external
include_directories(${MPI_C_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})
# intrinsic
include_directories("${MACE_PROJECT_SRC_DIR}/application")
include_directories("${MACE_PROJECT_SRC_DIR}/framework")

# Framework
add_subdirectory("framework/MACE")
# Application
add_subdirectory("application/MACE")
# Test
if(MACE_BUILD_TEST)
    add_subdirectory("test/MACE")
endif()
