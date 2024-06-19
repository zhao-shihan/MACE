file(GLOB_RECURSE SmearMACE_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable(SmearMACE ${SmearMACE_srcs})
target_link_libraries(SmearMACE MACEData MACEDetector Mustard::Mustard)

file(GLOB SimEMC_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimEMC_SCRIPTS})
    configure_file(${_scripts} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SmearMACE DESTINATION bin)
foreach(_scripts ${SmearMACE_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SmearMACE)
endforeach()
