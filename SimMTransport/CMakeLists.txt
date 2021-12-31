project(SimMTransport)

include_directories(${MPI_INCLUDE_PATH})
include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB SimMTransport_SOURCES ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(SimMTransport_static ${SimMTransport_SOURCES})
target_link_libraries(SimMTransport_static ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

add_executable(SimMTransport SimMTransport.cxx)
target_link_libraries(SimMTransport SimMTransport_static ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

configure_file(${PROJECT_SOURCE_DIR}/sample.cfg ${PROJECT_BINARY_DIR} COPYONLY)

install(TARGETS SimMTransport DESTINATION ${MACE_BINARY_INSTALL_DIR})
install(FILES ${PROJECT_SOURCE_DIR}/sample.cfg DESTINATION ${MACE_BINARY_INSTALL_DIR})
