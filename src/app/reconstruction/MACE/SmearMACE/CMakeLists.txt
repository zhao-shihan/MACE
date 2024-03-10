project(MACE)

file(GLOB_RECURSE SmearMACE_srcs ${PROJECT_SOURCE_DIR}/*.c++)

add_executable(SmearMACE ${SmearMACE_srcs})
target_link_libraries(SmearMACE MACEDataModel MACEDetector MACEFramework)
target_include_directories(SmearMACE PRIVATE ${GENFIT_INCLUDE_DIRS})

install(TARGETS SmearMACE DESTINATION bin)
