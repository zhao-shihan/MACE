# file(GLOB_RECURSE MACE_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++)


# add_executable(GetSamplingObj ${CMAKE_CURRENT_SOURCE_DIR}/src/GetSamplingObj.c++)
# set_target_properties(GetSamplingObj PROPERTIES
    # RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
# )

# target_link_libraries(GetSamplingObj PUBLIC Mustard::Mustard)


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test/scripts)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/
     DESTINATION ${CMAKE_BINARY_DIR}/test/scripts
     FILES_MATCHING PATTERN "*")
     
