file(GLOB_RECURSE SimMACEPhaseI_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimMACEPhaseI ${SimMACEPhaseI_srcs})
target_link_libraries(SimMACEPhaseI MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimMACEPhaseI_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimMACEPhaseI_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimMACEPhaseI DESTINATION bin)
foreach(_scripts ${SimMACEPhaseI_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimMACEPhaseI)
endforeach()
