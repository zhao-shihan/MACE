message(STATUS "Looking for envparse")

set(MACE_ENVPARSE_MINIMUM_REQUIRED 0.0.1)

if(NOT MACE_BUILTIN_ENVPARSE)
    find_package(envparse ${MACE_ENVPARSE_MINIMUM_REQUIRED} QUIET)
    if(NOT envparse_FOUND)
        set(MACE_BUILTIN_ENVPARSE ON)
        message(NOTICE "***Notice: envparse not found (minimum required is ${MACE_ENVPARSE_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_ENVPARSE")
    endif()
endif()

if(MACE_BUILTIN_ENVPARSE)
    message(STATUS "MACE will use built-in envparse")
    # check built-in version
    if(MACE_BUILTIN_ENVPARSE_VERSION VERSION_LESS MACE_ENVPARSE_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_ENVPARSE_VERSION is ${MACE_BUILTIN_ENVPARSE_VERSION}, which is less than the requirement (${MACE_ENVPARSE_MINIMUM_REQUIRED}). Changing to ${MACE_ENVPARSE_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_ENVPARSE_VERSION ${MACE_ENVPARSE_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_ENVPARSE_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/envparse-main")
    set(MACE_BUILTIN_ENVPARSE_URL "https://github.com/zhao-shihan/envparse/archive/refs/heads/main.zip")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_ENVPARSE_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(envparse SOURCE_DIR "${MACE_BUILTIN_ENVPARSE_SRC_DIR}")
        message(STATUS "Reusing envparse source ${MACE_BUILTIN_ENVPARSE_SRC_DIR}")
    else()
        FetchContent_Declare(envparse SOURCE_DIR "${MACE_BUILTIN_ENVPARSE_SRC_DIR}"
                                      URL "${MACE_BUILTIN_ENVPARSE_URL}")
        message(STATUS "envparse will be downloaded from ${MACE_BUILTIN_ENVPARSE_URL} to ${MACE_BUILTIN_ENVPARSE_SRC_DIR}")
    endif()
    # set options
    set(ENVPARSE_INSTALL ON CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring envparse (version: ${MACE_BUILTIN_ENVPARSE_VERSION})")
    FetchContent_MakeAvailable(envparse)
    message(STATUS "Downloading (if required) and configuring envparse (version: ${MACE_BUILTIN_ENVPARSE_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_ENVPARSE_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/envparse-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/envparse-subbuild")
        message(FATAL_ERROR "It seems that the download of envparse is not successful. You can try to run cmake again, or manually download envparse from ${MACE_BUILTIN_ENVPARSE_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_ENVPARSE)
    message(STATUS "Looking for envparse - found (version: ${envparse_VERSION})")
else()
    message(STATUS "Looking for envparse - built-in (version: ${MACE_BUILTIN_ENVPARSE_VERSION})")
endif()
