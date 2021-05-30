cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(MACE)

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

# MACE include
include_directories(${PROJECT_SOURCE_DIR}/include)

# MACE sources and headers
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc 
                  ${PROJECT_SOURCE_DIR}/src/fields/*.cc
                  ${PROJECT_SOURCE_DIR}/src/hit/*.cc
                  ${PROJECT_SOURCE_DIR}/src/messenger/*.cc
                  ${PROJECT_SOURCE_DIR}/src/physics/*.cc
                  ${PROJECT_SOURCE_DIR}/src/SD/*.cc
                  ${PROJECT_SOURCE_DIR}/src/useraction/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh
                  ${PROJECT_SOURCE_DIR}/include/fields/*.hh
                  ${PROJECT_SOURCE_DIR}/include/hit/*.hh
                  ${PROJECT_SOURCE_DIR}/include/messenger/*.hh
                  ${PROJECT_SOURCE_DIR}/include/physics/*.hh
                  ${PROJECT_SOURCE_DIR}/include/SD/*.hh
                  ${PROJECT_SOURCE_DIR}/include/useraction/*.hh)

add_executable(MACE MACE.cc ${sources} ${headers})
target_link_libraries(MACE ${Geant4_LIBRARIES})
target_link_libraries(MACE ${ROOT_LIBRARIES} )

set(MACE_MACROS
    init_vis.mac
    run.mac
    vis.mac
)
foreach(_macros ${MACE_MACROS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/macros/${_macros}
        ${PROJECT_BINARY_DIR}/${_macros}
        COPYONLY
    )
endforeach()

set(MACE_ANALYSIS
    MACE.ipynb
)
foreach(_analysis ${MACE_ANALYSIS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/analysis/${_analysis}
        ${PROJECT_BINARY_DIR}/analysis/${_analysis}
        COPYONLY
    )
endforeach()

# install(TARGETS MACE DESTINATION bin)
