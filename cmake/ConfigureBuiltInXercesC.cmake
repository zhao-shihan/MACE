function(mace_configure_built_in_xerces_c BUILTIN_XERCES_C_DIR)
    message(STATUS "---------------------------------------------------------------------------")
    message(STATUS "Configuring built-in Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED}")
    message(STATUS "---------------------------------------------------------------------------")

    # set Xerces-C++ options
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/.mace_fake_install_dump_for_built_in_libs" CACHE STRING "" FORCE)

    # to find CMake generated xercesc/util/Xercesxxxxxx.hpp
    cmake_path(RELATIVE_PATH BUILTIN_XERCES_C_DIR BASE_DIRECTORY "${MACE_PROJECT_ROOT_DIR}"
               OUTPUT_VARIABLE BUILTIN_XERCES_C_DIR_RELATIVE)
    include_directories("${CMAKE_BINARY_DIR}/${BUILTIN_XERCES_C_DIR_RELATIVE}/src")

    # configure Xerces-C++
    add_subdirectory("${BUILTIN_XERCES_C_DIR}")

    message(STATUS "---------------------------------------------------------------------------")
    message(STATUS "Configuring built-in Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} - done")
    message(STATUS "---------------------------------------------------------------------------")
endfunction()
