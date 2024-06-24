file(GLOB_RECURSE SimMMS_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimMMS ${SimMMS_srcs})
target_link_libraries(SimMMS MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimMMS_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimMMS_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimMMS DESTINATION ${CMAKE_INSTALL_BINDIR})
foreach(_scripts ${SimMMS_SCRIPTS})
    install(FILES ${_scripts} DESTINATION ${MACE_DATAROOTDIR}/SimMMS)
endforeach()
