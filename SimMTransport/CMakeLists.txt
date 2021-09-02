project(SimMTransport)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(SimMTransport SimMTransport.cc ${sources} ${headers})
target_link_libraries(SimMTransport ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

add_library(SimMTransportLib ${sources} ${headers})
target_link_libraries(SimMTransportLib ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

configure_file(${PROJECT_SOURCE_DIR}/sample.cfg ${PROJECT_BINARY_DIR} COPYONLY)

install(TARGETS SimMTransport DESTINATION bin)
