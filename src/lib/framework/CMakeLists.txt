project(MACE)

file(GLOB_RECURSE MACE_FRAMEWORK_SRC ${PROJECT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEFramework STATIC ${MACE_FRAMEWORK_SRC})
# Myself :)
target_include_directories(MACEFramework PUBLIC ${MACE_PROJECT_SRC_DIR}/lib/framework)
target_compile_options(MACEFramework PUBLIC ${MACE_COMPILE_OPTIONS})
target_compile_definitions(MACEFramework PUBLIC ${MACE_COMPILE_DEFINITIONS})
# Mustard
target_link_libraries(MACEFramework PUBLIC Mustard::Mustard)
