# file(GLOB_RECURSE MACE_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++)


# add_executable(GetSample ${CMAKE_CURRENT_SOURCE_DIR}/src/GetSample.c++)
# set_target_properties(GetSample PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
# )

# target_link_libraries(GetSample PUBLIC Mustard::Mustard)


# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test/scripts)

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/
#     DESTINATION ${CMAKE_BINARY_DIR}/test/scripts
#     FILES_MATCHING PATTERN "*")


file(GLOB Test_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(_scripts ${Test_SCRIPTS})
    set(Test_SCRIPTS_COPY_DIR test)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${Test_SCRIPTS_COPY_DIR})
    configure_file(${_scripts} ${CMAKE_BINARY_DIR}/${Test_SCRIPTS_COPY_DIR} COPYONLY)
    install(FILES ${_scripts} DESTINATION ${MACE_DATAROOTDIR}/${Test_SCRIPTS_COPY_DIR})
endforeach()

