project(MACE)

file(GLOB_RECURSE MACE_FRAMEWORK_SRC ${PROJECT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEFramework STATIC ${MACE_FRAMEWORK_SRC})
target_include_directories(MACEFramework PUBLIC ${MACE_PROJECT_SRC_DIR}/lib/framework)
# argparse
target_link_libraries(MACEFramework argparse::argparse)
# backward-cpp (Note: DO NOT link to Backward::Backward, just include the header and include/link to its dependencies)
target_compile_definitions(MACEFramework PUBLIC ${BACKWARD_DEFINITIONS})
target_include_directories(MACEFramework PUBLIC ${BACKWARD_INCLUDE_DIRS})
if(LIBDW_INCLUDE_DIR AND LIBDW_LIBRARY)
    target_include_directories(MACEFramework PUBLIC ${LIBDW_INCLUDE_DIR})
    target_link_libraries(MACEFramework ${LIBDW_LIBRARY})
endif()
if(LIBBFD_INCLUDE_DIR AND LIBBFD_LIBRARY)
    target_include_directories(MACEFramework PUBLIC ${LIBBFD_INCLUDE_DIR})
    target_link_libraries(MACEFramework ${LIBBFD_LIBRARY})
endif()
if(LIBDWARF_INCLUDE_DIR AND LIBELF_INCLUDE_DIR AND LIBDWARF_LIBRARY AND LIBELF_LIBRARY)
    target_include_directories(MACEFramework PUBLIC ${LIBDWARF_INCLUDE_DIR}
                                                    ${LIBELF_INCLUDE_DIR})
    target_link_libraries(MACEFramework ${LIBDWARF_LIBRARY}
                                        ${LIBELF_LIBRARY})
endif()
# fmt
target_link_libraries(MACEFramework fmt::fmt)
# Eigen
target_link_libraries(MACEFramework Eigen3::Eigen)
# Microsoft.GSL
target_link_libraries(MACEFramework Microsoft.GSL::GSL)
# yaml-cpp
target_link_libraries(MACEFramework yaml-cpp)
# MPI
target_link_libraries(MACEFramework MPI::MPI_C)
# Geant4
target_link_libraries(MACEFramework ${Geant4_LIBRARIES})
# ROOT
target_link_libraries(MACEFramework ROOT::Core ROOT::Hist ROOT::Tree ROOT::MathCore ROOT::ROOTDataFrame)
# options & definitions
target_compile_options(MACEFramework PUBLIC ${MACE_COMPILE_OPTIONS})
target_compile_definitions(MACEFramework PUBLIC ${MACE_COMPILE_DEFINITIONS})
