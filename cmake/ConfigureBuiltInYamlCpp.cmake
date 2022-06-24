function(mace_configure_built_in_yaml_cpp BUILTIN_YAML_CPP_DIR)
    message(STATUS "---------------------------------------------------------------------------")
    message(STATUS "Configuring built-in yaml-cpp")
    message(STATUS "---------------------------------------------------------------------------")

    # set yaml-cpp options
    set(YAML_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(YAML_CPP_INSTALL OFF CACHE BOOL "" FORCE)
    set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    if(MACE_USE_SHARED_MSVC_RT)
        set(YAML_MSVC_SHARED_RT ON CACHE BOOL "" FORCE)
    else()
        set(YAML_MSVC_SHARED_RT OFF CACHE BOOL "" FORCE)
    endif()

    # configure it
    add_subdirectory(${BUILTIN_YAML_CPP_DIR})

    message(STATUS "---------------------------------------------------------------------------")
    message(STATUS "Configuring built-in yaml-cpp - done")
    message(STATUS "---------------------------------------------------------------------------")
endfunction()
