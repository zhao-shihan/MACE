project(SimG4)

# SimG4 include
include_directories(${PROJECT_SOURCE_DIR}/include) 
include_directories(${PROJECT_SOURCE_DIR}/../SimMTransport/include)

# SimG4 sources and headers
file(GLOB_RECURSE SimG4_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE SimG4_HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(SimG4 SimG4.cc ${SimG4_SOURCES} ${SimG4_HEADERS})
target_link_libraries(SimG4 ${Geant4_LIBRARIES} ${G4mpi_LIBRARIES} ${ROOT_LIBRARIES} SimMTransportLib)

file(GLOB SimG4_MACROS ${PROJECT_SOURCE_DIR}/macros/*.mac)
foreach(_macros ${SimG4_MACROS})
    configure_file(${_macros} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimG4 DESTINATION bin)
