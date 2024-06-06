project(MACE)

file(GLOB_RECURSE MACE_FRAMEWORK_SRC ${PROJECT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEFramework STATIC ${MACE_FRAMEWORK_SRC})
# Myself :)
target_include_directories(MACEFramework PUBLIC ${MACE_PROJECT_SRC_DIR}/lib/framework)
target_compile_options(MACEFramework PUBLIC ${MACE_COMPILE_OPTIONS})
target_compile_definitions(MACEFramework PUBLIC ${MACE_COMPILE_DEFINITIONS})
# TimSort
target_link_libraries(MACEFramework PUBLIC timsort)
# muc
target_link_libraries(MACEFramework PUBLIC muc)
# argparse
target_link_libraries(MACEFramework PUBLIC argparse::argparse)
# Microsoft.GSL
target_link_libraries(MACEFramework PUBLIC Microsoft.GSL::GSL)
# backward-cpp
target_include_directories(MACEFramework PRIVATE ${BACKWARD_INCLUDE_DIRS})
target_compile_definitions(MACEFramework PRIVATE ${BACKWARD_DEFINITIONS})
if(LIBDW_LIBRARY)
    target_link_libraries(MACEFramework PRIVATE ${LIBDW_LIBRARY})
endif()
if(LIBBFD_LIBRARY)
    target_link_libraries(MACEFramework PRIVATE ${LIBBFD_LIBRARY})
endif()
if(LIBDWARF_LIBRARY AND LIBELF_LIBRARY)
    target_link_libraries(MACEFramework PRIVATE ${LIBDWARF_LIBRARY} ${LIBELF_LIBRARY})
endif()
# fmt
target_link_libraries(MACEFramework PUBLIC fmt::fmt)
# Eigen
target_link_libraries(MACEFramework PUBLIC Eigen3::Eigen)
# yaml-cpp
target_link_libraries(MACEFramework PUBLIC yaml-cpp)
# MPI
target_link_libraries(MACEFramework PUBLIC MPI::MPI_C)
# Geant4
target_link_libraries(MACEFramework PUBLIC ${Geant4_LIBRARIES})
# ROOT
target_link_libraries(MACEFramework PUBLIC ROOT::Core ROOT::Hist ROOT::Tree ROOT::MathCore ROOT::ROOTDataFrame ROOT::Geom)
