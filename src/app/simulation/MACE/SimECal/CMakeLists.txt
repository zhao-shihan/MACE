file(GLOB_RECURSE SimECal_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimECal ${SimECal_srcs})
target_link_libraries(SimECal MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimECal_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimECal_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimECal DESTINATION ${CMAKE_INSTALL_BINDIR})
foreach(_scripts ${SimECal_SCRIPTS})
    install(FILES ${_scripts} DESTINATION ${MACE_DATAROOTDIR}/SimECal)
endforeach()

