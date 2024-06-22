file(GLOB_RECURSE SimTarget_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimTarget ${SimTarget_srcs})
target_link_libraries(SimTarget MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimTarget_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimTarget_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimTarget DESTINATION bin)
foreach(_scripts ${SimTarget_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimTarget)
endforeach()
