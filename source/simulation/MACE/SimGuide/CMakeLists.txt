project(MACE)

# SimGuide sources
file(GLOB_RECURSE SimGuide_srcs ${PROJECT_SOURCE_DIR}/*.c++)

# targets
add_executable(SimGuide ${SimGuide_srcs})
target_link_libraries(SimGuide MACEDataModel MACEFramework MACEDetector)

file(GLOB SimGuide_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${SimGuide_SCRIPTS})
    configure_file(${_scripts} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()

install(TARGETS SimGuide DESTINATION bin)
foreach(_scripts ${SimGuide_SCRIPTS})
    install(FILES ${_scripts} DESTINATION share/SimGuide)
endforeach()
