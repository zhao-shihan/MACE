cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(MACE)

# MPI
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_DIRS})

# Geant4
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()
# G4mpi
find_package(G4mpi REQUIRED)
include(${Geant4_USE_FILE})

# ROOT
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/Global/include)

add_subdirectory(SimG4)
add_subdirectory(SimMuTransport)
