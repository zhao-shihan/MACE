message(STATUS "Looking for Eigen")

set(MACE_EIGEN_MINIMUM_REQUIRED 3.3.0)

if(NOT MACE_BUILTIN_EIGEN)
    find_package(Eigen3 ${MACE_EIGEN_MINIMUM_REQUIRED} QUIET)
    if(NOT EIGEN3_FOUND)
        set(MACE_BUILTIN_EIGEN ON)
        message(NOTICE "***Notice: Eigen not found (minimum required is ${MACE_EIGEN_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_EIGEN")
    endif()
endif()

# looking for eigen in MACE_PROJECT_3RDPARTY_DIR
function(mace_find_built_in_eigen EIGEN_FOUND EIGEN_DIR_IF_FOUND EIGEN_VERSION_IF_FOUND)
    # find possible eigen
    file(GLOB MACE_BUILTIN_EIGEN3_SIGNATURE_FILE_LIST "${MACE_PROJECT_3RDPARTY_DIR}/eigen-*/signature_of_eigen3_matrix_library")
    if("${MACE_BUILTIN_EIGEN3_SIGNATURE_FILE_LIST}" STREQUAL "")
        # if nothing found then we need to download it
        message(VERBOSE "Could not find any Eigen in ${MACE_PROJECT_3RDPARTY_DIR}")
        set(${EIGEN_FOUND} FALSE PARENT_SCOPE)
        set(${EIGEN_DIR_IF_FOUND} "" PARENT_SCOPE)
        set(${EIGEN_VERSION_IF_FOUND} 0 PARENT_SCOPE)
    else()
        # if found we dont check it yet, simply check for the existence of Eigen/Core
        set(EIGEN_DIR_LIST "")
        # check if have Eigen/Core, if have then put it into the list
        foreach(EIGEN3_SIGNATURE_FILE IN LISTS MACE_BUILTIN_EIGEN3_SIGNATURE_FILE_LIST)
            cmake_path(GET EIGEN3_SIGNATURE_FILE
                       PARENT_PATH EIGEN_DIR_CANDIDATE)
            if(EXISTS "${EIGEN_DIR_CANDIDATE}/Eigen/Core")
                list(APPEND EIGEN_DIR_LIST "${EIGEN_DIR_CANDIDATE}")
            endif()
        endforeach()
        # find the highest version among them
        set(EIGEN_DIR_BEST "")
        set(EIGEN_VERSION_BEST 0)
        foreach(EIGEN_DIR IN LISTS EIGEN_DIR_LIST)
            # just check its version by suffix, no better solution yet.
            # first get its directory name
            cmake_path(RELATIVE_PATH EIGEN_DIR BASE_DIRECTORY "${MACE_PROJECT_3RDPARTY_DIR}"
                       OUTPUT_VARIABLE EIGEN_DIR_NAME)
            # get its suffix by split via "-",
            string(REPLACE "-" ";" EIGEN_DIR_NAME_SPLIT "${EIGEN_DIR_NAME}")
            # and take the "1" component (eigen-x.x.x, eigen is "0", x.x.x is "1". if have suffix like rc, they are at "2".)
            list(GET EIGEN_DIR_NAME_SPLIT 1 EIGEN_VERSION)
            if(EIGEN_VERSION VERSION_GREATER EIGEN_VERSION_BEST)
                set(EIGEN_DIR_BEST "${EIGEN_DIR}")
                set(EIGEN_VERSION_BEST ${EIGEN_VERSION})
            endif()
        endforeach()
        # if fulfill the requirement then need not to download, else download.
        if(EIGEN_VERSION_BEST VERSION_GREATER_EQUAL MACE_EIGEN_MINIMUM_REQUIRED)
            message(VERBOSE "Eigen found in ${MACE_PROJECT_3RDPARTY_DIR} (version: ${EIGEN_VERSION_BEST})")
            set(${EIGEN_FOUND} TRUE PARENT_SCOPE)
            set(${EIGEN_DIR_IF_FOUND} "${EIGEN_DIR_BEST}" PARENT_SCOPE)
            set(${EIGEN_VERSION_IF_FOUND} ${EIGEN_VERSION_BEST} PARENT_SCOPE)
        else()
            message(VERBOSE "Eigen found in ${MACE_PROJECT_3RDPARTY_DIR} (version: ${EIGEN_VERSION_BEST}), but does not reach the minimum requirement (${MACE_EIGEN_MINIMUM_REQUIRED})")
            set(${EIGEN_FOUND} FALSE PARENT_SCOPE)
            set(${EIGEN_DIR_IF_FOUND} "" PARENT_SCOPE)
            set(${EIGEN_VERSION_IF_FOUND} 0 PARENT_SCOPE)
        endif()
    endif()
endfunction()

include(${MACE_PROJECT_CMAKE_DIR}/DownloadSmallFile.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/UnpackSmallTar.cmake)

if(MACE_BUILTIN_EIGEN)
    message(STATUS "MACE will use built-in Eigen")
    cmake_path(RELATIVE_PATH MACE_PROJECT_3RDPARTY_DIR BASE_DIRECTORY "${CMAKE_BINARY_DIR}"
               OUTPUT_VARIABLE MACE_PROJECT_3RDPARTY_DIR_RELATIVE)
    message(STATUS "Looking for Eigen in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE}")
    # looking for eigen in MACE_PROJECT_3RDPARTY_DIR
    mace_find_built_in_eigen(MACE_BUILTIN_EIGEN_FOUND MACE_BUILTIN_EIGEN_DIR MACE_BUILTIN_EIGEN_VERSION)
    # if found in MACE_PROJECT_3RDPARTY_DIR, use it. otherwise download it
    if(NOT MACE_BUILTIN_EIGEN_FOUND)
        message(NOTICE "***Notice: Eigen not found in directory of 3rd-party dependencies (minimum required is ${MACE_EIGEN_MINIMUM_REQUIRED}). It will be downloaded")
        # check download version
        if(MACE_DOWNLOAD_EIGEN_VERSION VERSION_LESS MACE_EIGEN_MINIMUM_REQUIRED)
            message(NOTICE "***Notice: Provided MACE_DOWNLOAD_EIGEN_VERSION is ${MACE_DOWNLOAD_EIGEN_VERSION}, which is less than the requirement (${MACE_EIGEN_MINIMUM_REQUIRED}). Changing to ${MACE_EIGEN_MINIMUM_REQUIRED}")
            set(MACE_DOWNLOAD_EIGEN_VERSION ${MACE_EIGEN_MINIMUM_REQUIRED})
        endif()
        # set download src and dest
        set(MACE_BUILTIN_EIGEN_ARCHIVE_SRC "https://gitlab.com/libeigen/eigen/-/archive/${MACE_DOWNLOAD_EIGEN_VERSION}/eigen-${MACE_DOWNLOAD_EIGEN_VERSION}.tar.gz")
        set(MACE_BUILTIN_EIGEN_ARCHIVE_DEST "${CMAKE_BINARY_DIR}/.cache/eigen-${MACE_DOWNLOAD_EIGEN_VERSION}.tar.gz")
        # download Eigen
        message(STATUS "Downloading Eigen archive")
        mace_download_small_file("${MACE_BUILTIN_EIGEN_ARCHIVE_SRC}" "${MACE_BUILTIN_EIGEN_ARCHIVE_DEST}")
        message(STATUS "Downloading Eigen archive - done")
        # untar Eigen
        message(STATUS "Unpacking Eigen archive")
        mace_unpack_small_tar("${MACE_BUILTIN_EIGEN_ARCHIVE_DEST}" "${MACE_PROJECT_3RDPARTY_DIR}")
        message(STATUS "Unpacking Eigen archive - done")
        # check again for safety
        mace_find_built_in_eigen(MACE_BUILTIN_EIGEN_FOUND MACE_BUILTIN_EIGEN_DIR MACE_BUILTIN_EIGEN_VERSION)
        if(NOT MACE_BUILTIN_EIGEN_FOUND)
            message(FATAL_ERROR "Eigen still remains invalid, even after the download procedure. This may be caused by an incomplete download, or by a corrupted directory structure. You can try to clean the build tree, delete all eigen-* directories under ${MACE_PROJECT_3RDPARTY_DIR}, then re-run CMake. If the download always fails, you can manually download Eigen from ${MACE_BUILTIN_EIGEN_ARCHIVE_SRC} and copy it to ${MACE_BUILTIN_EIGEN_ARCHIVE_DEST} (and keep the file name), or directly unpack it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure).")
        endif()
    endif()
    # report
    if(NOT DEFINED MACE_BUILTIN_EIGEN_ARCHIVE_DEST)
        message(STATUS "Looking for Eigen in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE} - found (version: ${MACE_BUILTIN_EIGEN_VERSION})")
    else()
        message(STATUS "Looking for Eigen in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE} - downloaded (version: ${MACE_BUILTIN_EIGEN_VERSION})")
    endif()
    # unset crap
    unset(MACE_BUILTIN_EIGEN_ARCHIVE_DEST)
    unset(MACE_BUILTIN_EIGEN_ARCHIVE_SRC)
    unset(MACE_PROJECT_3RDPARTY_DIR_RELATIVE)
    # set env
    set(EIGEN3_INCLUDE_DIR "${MACE_BUILTIN_EIGEN_DIR}")
endif()

message(STATUS "MACE will use Eigen headers from: ${EIGEN3_INCLUDE_DIR}")

if(NOT MACE_BUILTIN_EIGEN)
    message(STATUS "Looking for Eigen - found (version: ${EIGEN3_VERSION_STRING})")
else()
    message(STATUS "Looking for Eigen - built-in (version: ${MACE_BUILTIN_EIGEN_VERSION})")
endif()
