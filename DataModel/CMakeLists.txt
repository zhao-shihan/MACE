project(DataModel)

include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB_RECURSE DataModel_SOURCES ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(DataModel ${DataModel_SOURCES})
target_link_libraries(DataModel ${ROOT_LIBRARIES})

install(TARGETS DataModel DESTINATION lib)