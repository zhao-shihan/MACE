project(SimMuTransport)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(SimMuTransportRun SimMuTransportRun.cc ${sources} ${headers})
target_link_libraries(SimMuTransportRun ${ROOT_LIBRARIES} ${MPI_LIBRARIES})
add_executable(SimMuTransportPost SimMuTransportPost.cc)
target_link_libraries(SimMuTransportPost ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

install(TARGETS SimMuTransportRun SimMuTransportPost DESTINATION bin)

