file(GLOB_RECURSE SimDose_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SimDose ${SimDose_srcs})
target_link_libraries(SimDose MACEData MACEDetector Mustard::Mustard MACESimulation)

file(GLOB SimDose_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimDose_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimDose DESTINATION ${CMAKE_INSTALL_BINDIR})
foreach(_scripts ${SimDose_SCRIPTS})
    install(FILES ${_scripts} DESTINATION ${MACE_DATAROOTDIR}/SimDose)
endforeach()
