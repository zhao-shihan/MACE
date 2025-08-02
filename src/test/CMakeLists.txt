file(GLOB_RECURSE MACE_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++)

# 1. 定义可执行文件，并指定输出目录为 build/test/
add_executable(GetSamplingObj ${CMAKE_CURRENT_SOURCE_DIR}/src/GetSamplingObj.c++)
set_target_properties(GetSamplingObj PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
)

# 2. 链接库
target_link_libraries(GetSamplingObj PUBLIC Mustard::Mustard)

# 3. 创建 build/test/scripts/ 目录
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test/scripts)

# 4. 复制源码中的 scripts/ 到 build/test/scripts/
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/
     DESTINATION ${CMAKE_BINARY_DIR}/test/scripts
     FILES_MATCHING PATTERN "*")
     
# set(Test_COPY_DIR test)
# add_subdirectory(scripts)
# foreach(_scripts ${Test_SCRIPTS})
#     file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${Test_SCRIPTS_COPY_DIR})
#     configure_file(${_scripts} ${CMAKE_BINARY_DIR}/${Test_SCRIPTS_COPY_DIR} COPYONLY)
#     install(FILES ${_scripts} DESTINATION ${MACE_DATAROOTDIR}/${Test_SCRIPTS_COPY_DIR})
# endforeach()
