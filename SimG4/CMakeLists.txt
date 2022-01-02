project(SimG4)

# SimG4 include
include_directories(${MPI_INCLUDE_PATH})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${MACE_THIRD_PARTY_DIR}/G4MPI/include)

# SimG4 sources
file(GLOB_RECURSE SimG4_SOURCES ${PROJECT_SOURCE_DIR}/*.cxx)

# targets
add_library(SimG4_static ${SimG4_SOURCES})
target_link_libraries(SimG4_static ${Geant4_LIBRARIES} G4mpi-static SimMTransport_static DataModel)

add_executable(SimG4 SimG4.cxx)
target_link_libraries(SimG4 SimG4_static ${Geant4_LIBRARIES} G4mpi-static SimMTransport_static DataModel)

file(GLOB SimG4_MACROS ${PROJECT_SOURCE_DIR}/macros/*.mac)
foreach(_macros ${SimG4_MACROS})
    configure_file(${_macros} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimG4 DESTINATION bin)
foreach(_macros ${SimG4_MACROS})
    install(FILES ${_macros} DESTINATION share/SimG4)
endforeach()