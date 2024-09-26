file(GLOB_RECURSE SimECAL_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimECAL ${SimECAL_srcs})
target_link_libraries(SimECAL MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimECAL_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimECAL_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimECAL DESTINATION ${CMAKE_INSTALL_BINDIR})
foreach(_scripts ${SimECAL_SCRIPTS})
    install(FILES ${_scripts} DESTINATION ${MACE_DATAROOTDIR}/SimECAL)
endforeach()

