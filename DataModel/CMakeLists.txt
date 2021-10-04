project(DataModel)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${CLHEP_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE DataModel_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)

add_library(DataModel ${DataModel_SOURCES})
target_link_libraries(DataModel ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES})

install(TARGETS DataModel DESTINATION lib)