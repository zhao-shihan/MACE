project(SimG4)

# SimG4 include
include_directories(${PROJECT_SOURCE_DIR}/include)

# SimG4 sources and headers
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(SimG4 SimG4.cc ${sources} ${headers})
target_link_libraries(SimG4 ${Geant4_LIBRARIES} ${G4mpi_LIBRARIES} ${ROOT_LIBRARIES})

set(SimG4_MACROS
    init_vis.mac
    run.mac
    vis.mac
)
foreach(_macros ${SimG4_MACROS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/macros/${_macros}
        ${PROJECT_BINARY_DIR}/${_macros}
        COPYONLY
    )
endforeach()

# set(SimG4_ANALYSIS
#     SimG4.ipynb
# )
# foreach(_analysis ${SimG4_ANALYSIS})
#     configure_file(
#         ${PROJECT_SOURCE_DIR}/analysis/${_analysis}
#         ${PROJECT_BINARY_DIR}/${_analysis}
#         COPYONLY
#     )
# endforeach()

install(TARGETS SimG4 DESTINATION bin)
