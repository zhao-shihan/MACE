project(MACE)

# SimMACE sources
file(GLOB_RECURSE SimMACE_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

# targets
add_executable(SimMACE ${SimMACE_srcs})
target_link_libraries(SimMACE MACE)

file(GLOB SimMACE_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimMACE_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimMACE DESTINATION bin)
foreach(_scripts ${SimMACE_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimMACE)
endforeach()
