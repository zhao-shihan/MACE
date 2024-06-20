file(GLOB_RECURSE SimPTS_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimPTS ${SimPTS_srcs})
target_link_libraries(SimPTS MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimPTS_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimPTS_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimPTS DESTINATION bin)
foreach(_scripts ${SimPTS_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimPTS)
endforeach()
