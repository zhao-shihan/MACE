project(SimMTransport)

file(GLOB SimMTransport_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(SimMTransport_static ${SimMTransport_srcs})
target_link_libraries(SimMTransport_static ${ROOT_LIBRARIES} ${MPI_CXX_LIBRARIES})

add_executable(SimMTransport SimMTransport.cxx)
target_link_libraries(SimMTransport SimMTransport_static)

configure_file(${PROJECT_SOURCE_DIR}/sample.cfg ${PROJECT_BINARY_DIR} COPYONLY)

install(TARGETS SimMTransport DESTINATION bin)
install(FILES ${PROJECT_SOURCE_DIR}/sample.cfg DESTINATION share/SimMTransport)

