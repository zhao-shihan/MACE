project(MACE)

file(GLOB_RECURSE MACE_FRAMEWORK_SRC ${PROJECT_SOURCE_DIR}/MACE/*.cxx)

add_library(MACEFrameWork STATIC ${MACE_FRAMEWORK_SRC})
target_include_directories(MACEFrameWork PUBLIC ${MACE_PROJECT_SRC_DIR}/framework)
# argparse
target_link_libraries(MACEFrameWork argparse::argparse)
# backward-cpp (Note: DO NOT link to Backward::Backward, just include the header and include/link to its dependencies)
target_compile_definitions(MACEFrameWork PUBLIC ${BACKWARD_DEFINITIONS})
target_include_directories(MACEFrameWork PUBLIC ${BACKWARD_INCLUDE_DIRS})
if(LIBDW_INCLUDE_DIR AND LIBDW_LIBRARY)
    target_include_directories(MACEFrameWork PUBLIC ${LIBDW_INCLUDE_DIR})
    target_link_libraries(MACEFrameWork ${LIBDW_LIBRARY})
endif()
if(LIBBFD_INCLUDE_DIR AND LIBBFD_LIBRARY)
    target_include_directories(MACEFrameWork PUBLIC ${LIBBFD_INCLUDE_DIR})
    target_link_libraries(MACEFrameWork ${LIBBFD_LIBRARY})
endif()
if(LIBDWARF_INCLUDE_DIR AND LIBELF_INCLUDE_DIR AND LIBDWARF_LIBRARY AND LIBELF_LIBRARY)
    target_include_directories(MACEFrameWork PUBLIC ${LIBDWARF_INCLUDE_DIR}
                                           ${LIBELF_INCLUDE_DIR})
    target_link_libraries(MACEFrameWork ${LIBDWARF_LIBRARY}
                               ${LIBELF_LIBRARY})
endif()
# Eigen
target_link_libraries(MACEFrameWork Eigen3::Eigen)
# Microsoft.GSL
target_link_libraries(MACEFrameWork Microsoft.GSL::GSL)
# yaml-cpp
target_link_libraries(MACEFrameWork yaml-cpp)
# MPI
target_link_libraries(MACEFrameWork MPI::MPI_C)
# Geant4
target_link_libraries(MACEFrameWork ${Geant4_LIBRARIES})
# ROOT
target_include_directories(MACEFrameWork PUBLIC ${ROOT_INCLUDE_DIRS})
target_link_libraries(MACEFrameWork ${ROOT_LIBRARIES})
