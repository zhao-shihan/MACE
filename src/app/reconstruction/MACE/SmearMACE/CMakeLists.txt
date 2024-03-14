project(MACE)

file(GLOB_RECURSE SmearMACE_srcs ${PROJECT_SOURCE_DIR}/*.c++)
add_executable(SmearMACE ${SmearMACE_srcs})
target_link_libraries(SmearMACE MACEDataModel MACEDetector MACEFramework)

file(GLOB SimEMC_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimEMC_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SmearMACE DESTINATION bin)
foreach(_scripts ${SmearMACE_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SmearMACE)
endforeach()
