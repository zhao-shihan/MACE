project(SimMTransport)

include_directories(${MPI_INCLUDE_PATH})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(SimMTransport-static ${sources} ${headers})
target_link_libraries(SimMTransport-static ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

add_executable(SimMTransport SimMTransport.cc ${headers})
target_link_libraries(SimMTransport ${ROOT_LIBRARIES} ${MPI_LIBRARIES} SimMTransport-static)

configure_file(${PROJECT_SOURCE_DIR}/sample.cfg ${PROJECT_BINARY_DIR} COPYONLY)

install(TARGETS SimMTransport DESTINATION ${MACE_BINARY_INSTALL_DIR})
install(FILES ${PROJECT_SOURCE_DIR}/sample.cfg DESTINATION ${MACE_BINARY_INSTALL_DIR})
