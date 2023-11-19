project(MACE)

file(GLOB_RECURSE SimTarget_srcs ${PROJECT_SOURCE_DIR}/*.c++)
add_executable(SimEMC ${SimTarget_srcs})
target_link_libraries(SimEMC MACEDataModel MACEDetector MACEFramework MACESimulation)

file(GLOB SimTarget_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimTarget_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimEMC DESTINATION bin)
foreach(_scripts ${SimTarget_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimEMC)
endforeach()

