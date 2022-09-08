message(STATUS "Looking for argparse")

set(MACE_ARGPARSE_MINIMUM_REQUIRED 2.6)

if(NOT MACE_BUILTIN_ARGPARSE)
    find_package(argparse "${MACE_ARGPARSE_MINIMUM_REQUIRED}.0" QUIET)
    if(NOT argparse_FOUND)
        set(MACE_BUILTIN_ARGPARSE ON)
        message(NOTICE "***Notice: argparse not found (minimum required is ${MACE_ARGPARSE_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_ARGPARSE")
    endif()
endif()

if(MACE_BUILTIN_ARGPARSE)
    message(STATUS "MACE will use built-in argparse")
    # check built-in version
    if(MACE_BUILTIN_ARGPARSE_VERSION VERSION_LESS MACE_ARGPARSE_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_ARGPARSE_VERSION is ${MACE_BUILTIN_ARGPARSE_VERSION}, which is less than the requirement (${MACE_ARGPARSE_MINIMUM_REQUIRED}). Changing to ${MACE_ARGPARSE_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_ARGPARSE_VERSION ${MACE_ARGPARSE_MINIMUM_REQUIRED})
    endif()
    # set download src and dest
    include(FetchContent)
    set(MACE_BUILTIN_ARGPARSE_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/argparse-${MACE_BUILTIN_ARGPARSE_VERSION}")
    set(MACE_BUILTIN_ARGPARSE_URL "https://github.com/p-ranav/argparse/archive/refs/tags/v${MACE_BUILTIN_ARGPARSE_VERSION}.tar.gz")
    if(EXISTS "${MACE_BUILTIN_ARGPARSE_SRC_DIR}/CMakeLists.txt")
        message(STATUS "Reusing argparse source ${MACE_BUILTIN_ARGPARSE_SRC_DIR}")
        FetchContent_Declare(argparse SOURCE_DIR "${MACE_BUILTIN_ARGPARSE_SRC_DIR}")
    else()
        message(STATUS "argparse will be downloaded from ${MACE_BUILTIN_ARGPARSE_URL} to ${MACE_BUILTIN_ARGPARSE_SRC_DIR}")
        FetchContent_Declare(argparse SOURCE_DIR "${MACE_BUILTIN_ARGPARSE_SRC_DIR}"
                                      URL "${MACE_BUILTIN_ARGPARSE_URL}")
    endif()
    # configure it
    message(STATUS "Downloading (if required) and configuring argparse (version: ${MACE_BUILTIN_ARGPARSE_VERSION})")
    FetchContent_MakeAvailable(argparse)
    message(STATUS "Downloading (if required) and configuring argparse (version: ${MACE_BUILTIN_ARGPARSE_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_ARGPARSE_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/argparse-subbuild")
        message(FATAL_ERROR "It seems that the download of argparse is not successful. You can try to run cmake again, or manually download argparse from ${MACE_BUILTIN_ARGPARSE_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_ARGPARSE)
    message(STATUS "Looking for argparse - found (version: ${argparse_VERSION})")
else()
    message(STATUS "Looking for argparse - built-in (version: ${MACE_BUILTIN_ARGPARSE_VERSION})")
endif()
