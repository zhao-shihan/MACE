project(SimMTransport)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(SimMTransportRun SimMTransportRun.cc ${sources} ${headers})
target_link_libraries(SimMTransportRun ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

configure_file(${PROJECT_SOURCE_DIR}/sample.cfg ${PROJECT_BINARY_DIR} COPYONLY)

install(TARGETS SimMTransportRun DESTINATION bin)

