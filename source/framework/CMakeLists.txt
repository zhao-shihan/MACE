project(MACE)

file(GLOB_RECURSE MACE_FRAMEWORK_SRC ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACE STATIC ${MACE_FRAMEWORK_SRC})
target_include_directories(MACE PUBLIC ${MACE_PROJECT_SRC_DIR}/framework)
# argparse
target_link_libraries(MACE argparse::argparse)
# backward-cpp (Note: DO NOT link to Backward::Backward, just include the header and include/link to its dependencies)
target_compile_definitions(MACE PUBLIC ${BACKWARD_DEFINITIONS})
target_include_directories(MACE PUBLIC ${BACKWARD_INCLUDE_DIRS})
if(LIBDW_INCLUDE_DIR AND LIBDW_LIBRARY)
    target_include_directories(MACE PUBLIC ${LIBDW_INCLUDE_DIR})
    target_link_libraries(MACE ${LIBDW_LIBRARY})
endif()
if(LIBBFD_INCLUDE_DIR AND LIBBFD_LIBRARY)
    target_include_directories(MACE PUBLIC ${LIBBFD_INCLUDE_DIR})
    target_link_libraries(MACE ${LIBBFD_LIBRARY})
endif()
if(LIBDWARF_INCLUDE_DIR AND LIBELF_INCLUDE_DIR AND LIBDWARF_LIBRARY AND LIBELF_LIBRARY)
    target_include_directories(MACE PUBLIC ${LIBDWARF_INCLUDE_DIR}
                                           ${LIBELF_INCLUDE_DIR})
    target_link_libraries(MACE ${LIBDWARF_LIBRARY}
                               ${LIBELF_LIBRARY})
endif()
# Eigen
target_link_libraries(MACE Eigen3::Eigen)
# Microsoft.GSL
target_link_libraries(MACE Microsoft.GSL::GSL)
# yaml-cpp
target_link_libraries(MACE yaml-cpp)
# MPI
target_link_libraries(MACE MPI::MPI_C)
# Geant4
target_link_libraries(MACE ${Geant4_LIBRARIES})
# ROOT
target_include_directories(MACE PUBLIC ${ROOT_INCLUDE_DIRS})
target_link_libraries(MACE ${ROOT_LIBRARIES})
