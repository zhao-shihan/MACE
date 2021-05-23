cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(PSIMACE)

# Geant4
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()
include(${Geant4_USE_FILE})

# # ROOT
# find_package(ROOT QUIET)
# if(NOT ROOT_FOUND)
#     message(STATUS "ROOT package not found")
#     return()
# else()
#     include_directories(${ROOT_INCLUDE_DIR})
# endif()

# PSIMACE include
include_directories(${PROJECT_SOURCE_DIR}/include)

# PSIMACE sources and headers
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp 
                  ${PROJECT_SOURCE_DIR}/src/fields/*.cpp
                  ${PROJECT_SOURCE_DIR}/src/messenger/*.cpp
                  ${PROJECT_SOURCE_DIR}/src/physics/*.cpp
                  ${PROJECT_SOURCE_DIR}/src/SD/*.cpp
                  ${PROJECT_SOURCE_DIR}/src/userAction/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh
                  ${PROJECT_SOURCE_DIR}/include/fields/*.hh
                  ${PROJECT_SOURCE_DIR}/include/messenger/*.hh
                  ${PROJECT_SOURCE_DIR}/include/physics/*.hh
                  ${PROJECT_SOURCE_DIR}/include/SD/*.hh
                  ${PROJECT_SOURCE_DIR}/include/userAction/*.hh)

add_executable(PSIMACE PSIMACE.cpp ${sources} ${headers})
target_link_libraries(PSIMACE ${Geant4_LIBRARIES})
target_link_libraries(PSIMACE ${ROOT_LIBRARIES} )

set(PSIMACE_MACROS
    init_vis.mac
    run.mac
    vis.mac
)
foreach(_macros ${PSIMACE_MACROS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/macros/${_macros}
        ${PROJECT_BINARY_DIR}/${_macros}
        COPYONLY
    )
endforeach()

# install(TARGETS PSIMACE DESTINATION bin)
