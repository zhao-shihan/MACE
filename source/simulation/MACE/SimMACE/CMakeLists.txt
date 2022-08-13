project(MACE)

# SimMACE sources
file(GLOB_RECURSE SimMACE_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

# targets
add_executable(SimMACE ${SimMACE_srcs})
target_link_libraries(SimMACE MACE)

file(GLOB SimMACE_MACROS ${PROJECT_SOURCE_DIR}/macros/*)
foreach(_macros ${SimMACE_MACROS})
    configure_file(${_macros} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimMACE DESTINATION bin)
foreach(_macros ${SimMACE_MACROS})
    install(FILES ${_macros} DESTINATION share/SimMACE)
endforeach()
