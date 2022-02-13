project(SimMACE)

# SimMACE include
include_directories(${MPI_INCLUDE_PATH})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${MACE_THIRD_PARTY_DIR}/G4MPI/include)

# SimMACE sources
file(GLOB_RECURSE SimMACE_SOURCES ${PROJECT_SOURCE_DIR}/*.cxx)

# targets
add_executable(SimMACE ${SimMACE_SOURCES})
target_link_libraries(SimMACE ${Geant4_LIBRARIES} G4mpi-static SimMTransport_static DataModel Geometry)

file(GLOB SimMACE_MACROS ${PROJECT_SOURCE_DIR}/macros/*.mac)
foreach(_macros ${SimMACE_MACROS})
    configure_file(${_macros} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimMACE DESTINATION bin)
foreach(_macros ${SimMACE_MACROS})
    install(FILES ${_macros} DESTINATION share/SimMACE)
endforeach()