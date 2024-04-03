project(MACE)

file(GLOB_RECURSE SimEMC_srcs ${PROJECT_SOURCE_DIR}/*.c++)
add_executable(SimEMC ${SimEMC_srcs})
target_link_libraries(SimEMC MACEData MACEDetector MACEFramework MACESimulation)

file(GLOB SimEMC_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimEMC_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimEMC DESTINATION bin)
foreach(_scripts ${SimEMC_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimEMC)
endforeach()

