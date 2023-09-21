# Usage:
# 1. Replace pmp with the standard name of the library (The name that find_package can find the library. If the library uses xxxConfig.cmake then it is xxx) (e.g. for yaml-cpp it is yaml-cpp, for Eigen3 it is Eigen).
# 2. Replace PMP with a full uppercase name same as (or at least similar to, if not convenient) pmp  (e.g. for yaml-cpp it is YAML_CPP, for Eigen3 it is EIGEN, for Microsoft-GSL it is MSGSL).
# 3. Replace 3.0.0 with the minimum version required for this library.
# 4. Replace pmp-library- with the directory name same as what the library archive extracts to.
# 5. Replace https://github.com/pmp-library/pmp-library/archive/refs/tags/3.0.0.tar.gz with the library archive download URL template, which should includes ${MACE_BUILTIN_PMP_VERSION} indicates the library version (e.g. for yaml-cpp it is https://github.com/jbeder/pmp/archive/refs/tags/${MACE_BUILTIN_PMP_VERSION}.tar.gz)
# 6. Add proper options between "reuse or download" section and "configure it" section.
# 7. Delete this guide text, and make other parts of this file prettier.
# 8. Set options MACE_BUILTIN_PMP and MACE_BUILTIN_PMP_VERSION in the main CMakeLists.txt.

message(STATUS "Looking for pmp")

set(MACE_PMP_MINIMUM_REQUIRED 3.0.0)

if(NOT MACE_BUILTIN_PMP)
    find_package(pmp ${MACE_PMP_MINIMUM_REQUIRED} QUIET)
    if(NOT pmp_FOUND)
        set(MACE_BUILTIN_PMP ON)
        message(NOTICE "***Notice: pmp not found (minimum required is ${MACE_PMP_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_PMP")
    endif()
endif()

if(MACE_BUILTIN_PMP)
    message(STATUS "MACE will use built-in pmp")
    # check built-in version
    if(MACE_BUILTIN_PMP_VERSION VERSION_LESS MACE_PMP_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_PMP_VERSION is ${MACE_BUILTIN_PMP_VERSION}, which is less than the requirement (${MACE_PMP_MINIMUM_REQUIRED}). Changing to ${MACE_PMP_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_PMP_VERSION ${MACE_PMP_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_PMP_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/pmp-library-${MACE_BUILTIN_PMP_VERSION}")
    set(MACE_BUILTIN_PMP_URL "https://github.com/pmp-library/pmp-library/archive/refs/tags/${MACE_BUILTIN_PMP_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_PMP_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(pmp SOURCE_DIR "${MACE_BUILTIN_PMP_SRC_DIR}")
        message(STATUS "Reusing pmp source ${MACE_BUILTIN_PMP_SRC_DIR}")
    else()
        FetchContent_Declare(pmp SOURCE_DIR "${MACE_BUILTIN_PMP_SRC_DIR}"
                                      URL "${MACE_BUILTIN_PMP_URL}")
        message(STATUS "pmp will be downloaded from ${MACE_BUILTIN_PMP_URL} to ${MACE_BUILTIN_PMP_SRC_DIR}")
    endif()
    # set options
    set(PMP_BUILD_EXAMPLES OFF)
    set(PMP_BUILD_TESTS OFF)
    set(PMP_BUILD_DOCS OFF)
    set(PMP_BUILD_VIS OFF)
    set(PMP_STRICT_COMPILATION OFF)
    # configure it
    message(STATUS "Downloading (if required) and configuring pmp (version: ${MACE_BUILTIN_PMP_VERSION})")
    FetchContent_MakeAvailable(pmp)
    message(STATUS "Downloading (if required) and configuring pmp (version: ${MACE_BUILTIN_PMP_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_PMP_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/pmp-subbuild")
        message(FATAL_ERROR "It seems that the download of pmp is not successful. You can try to run cmake again, or manually download pmp from ${MACE_BUILTIN_PMP_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_PMP)
    message(STATUS "Looking for pmp - found (version: ${pmp_VERSION})")
else()
    message(STATUS "Looking for pmp - built-in (version: ${MACE_BUILTIN_PMP_VERSION})")
endif()
