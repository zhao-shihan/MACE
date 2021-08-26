project(SimMTransport)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(SimMTransportRun SimMTransportRun.cc ${sources} ${headers})
target_link_libraries(SimMTransportRun ${ROOT_LIBRARIES} ${MPI_LIBRARIES})
add_executable(SimMTransportPost SimMTransportPost.cc)
target_link_libraries(SimMTransportPost ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

install(TARGETS SimMTransportRun SimMTransportPost DESTINATION bin)

