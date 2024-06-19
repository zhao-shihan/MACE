file(GLOB_RECURSE SimMACE_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimMACE ${SimMACE_srcs})
target_link_libraries(SimMACE MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimMACE_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimMACE_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimMACE DESTINATION bin)
foreach(_scripts ${SimMACE_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimMACE)
endforeach()
