message(STATUS "Looking for Eigen")

set(MACE_EIGEN_MINIMUM_REQUIRED 3.3.0)

if(NOT MACE_BUILTIN_EIGEN)
    find_package(Eigen3 ${MACE_EIGEN_MINIMUM_REQUIRED} QUIET)
    if(NOT Eigen3_FOUND)
        set(MACE_BUILTIN_EIGEN ON)
        message(NOTICE "***Notice: Eigen not found (minimum required is ${MACE_EIGEN_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_EIGEN")
    endif()
endif()

if(MACE_BUILTIN_EIGEN)
    message(STATUS "MACE will use built-in Eigen")
    # check built-in version
    if(MACE_BUILTIN_EIGEN_VERSION VERSION_LESS MACE_EIGEN_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_EIGEN_VERSION is ${MACE_BUILTIN_EIGEN_VERSION}, which is less than the requirement (${MACE_EIGEN_MINIMUM_REQUIRED}). Changing to ${MACE_EIGEN_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_EIGEN_VERSION ${MACE_EIGEN_MINIMUM_REQUIRED})
    endif()
    # set download src and dest
    include(FetchContent)
    set(MACE_BUILTIN_EIGEN_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/eigen-${MACE_BUILTIN_EIGEN_VERSION}")
    set(MACE_BUILTIN_EIGEN_URL "https://gitlab.com/libeigen/eigen/-/archive/${MACE_BUILTIN_EIGEN_VERSION}/eigen-${MACE_BUILTIN_EIGEN_VERSION}.tar.bz2")
    if(EXISTS "${MACE_BUILTIN_EIGEN_SRC_DIR}/CMakeLists.txt")
        message(STATUS "Reusing Eigen source ${MACE_BUILTIN_EIGEN_SRC_DIR}")
        FetchContent_Declare(Eigen3 SOURCE_DIR "${MACE_BUILTIN_EIGEN_SRC_DIR}")
    else()
        message(STATUS "Eigen will be downloaded from ${MACE_BUILTIN_EIGEN_URL} to ${MACE_BUILTIN_EIGEN_SRC_DIR}")
        FetchContent_Declare(Eigen3 SOURCE_DIR "${MACE_BUILTIN_EIGEN_SRC_DIR}"
                                    URL "${MACE_BUILTIN_EIGEN_URL}")
    endif()
    # configure it
    message(STATUS ">>>>>>>> Downloading (if required) and configuring built-in Eigen (version: ${MACE_BUILTIN_EIGEN_VERSION})")
    FetchContent_MakeAvailable(Eigen3)
    message(STATUS "<<<<<<<< Downloading (if required) and configuring built-in Eigen (version: ${MACE_BUILTIN_EIGEN_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_EIGEN_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/eigen3-subbuild")
        message(FATAL_ERROR "It seems that the download of Eigen is not successful. You can try to run cmake again, or manually download Eigen from ${MACE_BUILTIN_EIGEN_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_EIGEN)
    message(STATUS "Looking for Eigen - found (version: ${Eigen3_VERSION})")
else()
    message(STATUS "Looking for Eigen - built-in (version: ${MACE_BUILTIN_EIGEN_VERSION})")
endif()
