function(mace_configure_built_in_xerces_c BUILTIN_XERCES_C_DIR)
    message(STATUS "---------------------------------------------------------------------------")
    message(STATUS "Configuring built-in Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED}")
    message(STATUS "---------------------------------------------------------------------------")

    # set Xerces-C++ options
    set(BUILD_SHARED_LIBS_STORE ${BUILD_SHARED_LIBS})
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    # redirect installation
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/.mace_fake_install_dump_for_built_in_libs")
    set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}")
    set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}")
    set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_PREFIX}")
    set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}")
    set(pkgconfig-dir_STORE "${pkgconfig-dir}")
    set(pkgconfig-dir "${CMAKE_INSTALL_PREFIX}" CACHE STRING "" FORCE)
    # to find CMake generated xercesc/util/Xercesxxxxxx.hpp
    cmake_path(RELATIVE_PATH BUILTIN_XERCES_C_DIR BASE_DIRECTORY "${MACE_PROJECT_ROOT_DIR}"
               OUTPUT_VARIABLE BUILTIN_XERCES_C_DIR_RELATIVE)
    include_directories("${CMAKE_BINARY_DIR}/${BUILTIN_XERCES_C_DIR_RELATIVE}/src")
    # configure Xerces-C++
    add_subdirectory("${BUILTIN_XERCES_C_DIR}")
    # restore vars
    set(pkgconfig-dir "${pkgconfig-dir_STORE}" CACHE STRING "" FORCE)
    unset(pkgconfig-dir_STORE)
    unset(CMAKE_INSTALL_INCLUDEDIR)
    unset(CMAKE_INSTALL_BINDIR)
    unset(CMAKE_INSTALL_DOCDIR)
    unset(CMAKE_INSTALL_LIBDIR)
    unset(CMAKE_INSTALL_PREFIX)
    set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_STORE} CACHE BOOL "" FORCE)
    unset(BUILD_SHARED_LIBS_STORE)
    # fix incorrect installations
    install(SCRIPT "${MACE_PROJECT_CMAKE_DIR}/PostFixBuiltInXercesCInstall.cmake")

    message(STATUS "---------------------------------------------------------------------------")
    message(STATUS "Configuring built-in Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} - done")
    message(STATUS "---------------------------------------------------------------------------")
endfunction()
