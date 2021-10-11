project(SimMTransport)

include_directories(${MPI_INCLUDE_PATH})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${CLHEP_INCLUDE_DIRS})

file(GLOB SimMTransport_SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

add_library(SimMTransport-static ${SimMTransport_SOURCES})
target_link_libraries(SimMTransport-static ${ROOT_LIBRARIES} ${MPI_LIBRARIES})

add_executable(SimMTransport SimMTransport.cc)
target_link_libraries(SimMTransport ${ROOT_LIBRARIES} ${MPI_LIBRARIES} SimMTransport-static)

configure_file(${PROJECT_SOURCE_DIR}/sample.cfg ${PROJECT_BINARY_DIR} COPYONLY)

install(TARGETS SimMTransport DESTINATION ${MACE_BINARY_INSTALL_DIR})
install(FILES ${PROJECT_SOURCE_DIR}/sample.cfg DESTINATION ${MACE_BINARY_INSTALL_DIR})
