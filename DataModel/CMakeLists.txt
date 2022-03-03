project(DataModel)

include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB_RECURSE DataModel_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(DataModel ${DataModel_srcs})
target_link_libraries(DataModel ${ROOT_LIBRARIES})
