project(MACE)

# SimTarget sources
file(GLOB_RECURSE SimTarget_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

# targets
add_executable(SimTarget ${SimTarget_srcs})
target_link_libraries(SimTarget MACE)

file(GLOB SimTarget_MACROS ${PROJECT_SOURCE_DIR}/macros/*.mac)
foreach(_macros ${SimTarget_MACROS})
    configure_file(${_macros} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimTarget DESTINATION bin)
foreach(_macros ${SimTarget_MACROS})
    install(FILES ${_macros} DESTINATION share/SimTarget)
endforeach()
