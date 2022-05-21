project(MACE)

if(NOT MACE_SHOW_ALL_COMPILER_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-Wno-stringop-truncation)
    endif()
endif()

file(GLOB_RECURSE MACEUtility_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACEUtility ${MACEUtility_srcs})
target_link_libraries(MACEUtility ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES})
