file(GLOB_RECURSE SimEMC_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimEMC ${SimEMC_srcs})
target_link_libraries(SimEMC MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimEMC_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimEMC_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimEMC DESTINATION ${CMAKE_INSTALL_BINDIR})
foreach(_scripts ${SimEMC_SCRIPTS})
    install(FILES ${_scripts} DESTINATION ${MACE_DATAROOTDIR}/SimEMC)
endforeach()

