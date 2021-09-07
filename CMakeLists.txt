cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(MACE)

set(CMAKE_CXX_STANDARD 17)

# MPI
find_package(MPI REQUIRED)

# Geant4
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

# ROOT
find_package(ROOT REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/Global/include)

add_subdirectory(Buildin)
add_subdirectory(SimG4)
add_subdirectory(SimMTransport)
