cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(MACE)

# MACE at C++17
set(CMAKE_CXX_STANDARD 17)

# MPI
find_package(MPI REQUIRED)

# Geant4
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

# ROOT
find_package(ROOT REQUIRED)

# EIGEN3
find_package(Eigen3 REQUIRED)

# Vars
set(MACE_PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(MACE_BINARY_INSTALL_DIR .)
set(MACE_LIBRARY_INSTALL_DIR .)

include_directories(${PROJECT_SOURCE_DIR}/Global/include)

# A useful function
function(include_directories_recursively root_dir)
    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            if(${sub} STREQUAL "include")
                include_directories(${root_dir}/${sub})
            else()
                include_directories_recursively(${root_dir}/${sub})
            endif()
        endif()
    endforeach()
endfunction()

add_subdirectory(Buildin)
add_subdirectory(SimG4)
add_subdirectory(SimMTransport)
add_subdirectory(Reconstruction)
