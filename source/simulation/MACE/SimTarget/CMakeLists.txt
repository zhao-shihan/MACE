project(MACE)

# SimTarget sources
file(GLOB_RECURSE SimTarget_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

# targets
add_executable(SimTarget ${SimTarget_srcs})
target_link_libraries(SimTarget MACEDataModel MACEFrameWork MACEGeometry)

file(GLOB SimTarget_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimTarget_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimTarget DESTINATION bin)
foreach(_scripts ${SimTarget_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimTarget)
endforeach()
