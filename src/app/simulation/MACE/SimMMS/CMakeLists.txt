file(GLOB_RECURSE SimMMS_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimMMS ${SimMMS_srcs})
target_link_libraries(SimMMS MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimMMS_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimMMS_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimMMS DESTINATION bin)
foreach(_scripts ${SimMMS_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimMMS)
endforeach()
