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

# MACE include
include_directories(${PROJECT_SOURCE_DIR}/include)

# MACE sources and headers
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(MACE MACE.cc ${sources} ${headers})
target_link_libraries(MACE ${Geant4_LIBRARIES} ${G4mpi_LIBRARIES} ${ROOT_LIBRARIES})

set(MACE_MACROS
    init_vis.mac
    run.mac
    vis.mac
)
foreach(_macros ${MACE_MACROS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/macros/${_macros}
        ${PROJECT_BINARY_DIR}/${_macros}
        COPYONLY
    )
endforeach()

# set(MACE_ANALYSIS
#     MACE.ipynb
# )
# foreach(_analysis ${MACE_ANALYSIS})
#     configure_file(
#         ${PROJECT_SOURCE_DIR}/analysis/${_analysis}
#         ${PROJECT_BINARY_DIR}/${_analysis}
#         COPYONLY
#     )
# endforeach()

install(TARGETS MACE DESTINATION bin)
