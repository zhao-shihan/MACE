message(STATUS "Looking for yaml-cpp")

set(MACE_YAML_CPP_MINIMUM_REQUIRED 0.6.0)

if(NOT MACE_BUILTIN_YAML_CPP)
    find_package(yaml-cpp ${MACE_YAML_CPP_MINIMUM_REQUIRED} QUIET)
    if(NOT yaml-cpp_FOUND)
        set(MACE_BUILTIN_YAML_CPP ON)
        message(NOTICE "***Notice: yaml-cpp not found (minimum required is ${MACE_YAML_CPP_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_YAML_CPP")
    endif()
endif()

# looking for yaml-cpp in MACE_PROJECT_3RDPARTY_DIR
function(mace_find_built_in_yaml_cpp YAML_CPP_FOUND YAML_CPP_DIR_IF_FOUND YAML_CPP_VERSION_IF_FOUND)
    # find possible yaml-cpp
    file(GLOB MACE_BUILTIN_YAML_CPP_CMAKELISTS_LIST "${MACE_PROJECT_3RDPARTY_DIR}/yaml-cpp-yaml-cpp-*/CMakeLists.txt")
    if("${MACE_BUILTIN_YAML_CPP_CMAKELISTS_LIST}" STREQUAL "")
        # if nothing found then we need to download it
        message(VERBOSE "Could not find any yaml-cpp in ${MACE_PROJECT_3RDPARTY_DIR}")
        set(${YAML_CPP_FOUND} FALSE PARENT_SCOPE)
        set(${YAML_CPP_DIR_IF_FOUND} "" PARENT_SCOPE)
        set(${YAML_CPP_VERSION_IF_FOUND} 0 PARENT_SCOPE)
    else()
        set(YAML_CPP_DIR_LIST "")
        # extract yaml-cpp dirs
        foreach(YAML_CPP_CMAKELISTS IN LISTS MACE_BUILTIN_YAML_CPP_CMAKELISTS_LIST)
            cmake_path(GET YAML_CPP_CMAKELISTS
                       PARENT_PATH YAML_CPP_DIR)
            list(APPEND YAML_CPP_DIR_LIST "${YAML_CPP_DIR}")
        endforeach()
        # find the highest version among them
        set(YAML_CPP_DIR_BEST "")
        set(YAML_CPP_VERSION_BEST 0)
        foreach(YAML_CPP_DIR IN LISTS YAML_CPP_DIR_LIST)
            # just check its version by suffix, no better solution yet.
            # first get its directory name
            cmake_path(RELATIVE_PATH YAML_CPP_DIR BASE_DIRECTORY "${MACE_PROJECT_3RDPARTY_DIR}"
                       OUTPUT_VARIABLE YAML_CPP_DIR_NAME)
            # get its suffix by split via "-",
            string(REPLACE "-" ";" YAML_CPP_DIR_NAME_SPLIT "${YAML_CPP_DIR_NAME}")
            # and take the "4" component (yaml-cpp-yaml-cpp-x.x.x, x.x.x is "4".)
            list(GET YAML_CPP_DIR_NAME_SPLIT 4 YAML_CPP_VERSION)
            if(YAML_CPP_VERSION VERSION_GREATER YAML_CPP_VERSION_BEST)
                set(YAML_CPP_DIR_BEST "${YAML_CPP_DIR}")
                set(YAML_CPP_VERSION_BEST ${YAML_CPP_VERSION})
            endif()
        endforeach()
        # if fulfill the requirement then need not to download, else download.
        if(YAML_CPP_VERSION_BEST VERSION_GREATER_EQUAL MACE_YAML_CPP_MINIMUM_REQUIRED)
            message(VERBOSE "yaml-cpp found in ${MACE_PROJECT_3RDPARTY_DIR} (version: ${YAML_CPP_VERSION_BEST})")
            set(${YAML_CPP_FOUND} TRUE PARENT_SCOPE)
            set(${YAML_CPP_DIR_IF_FOUND} "${YAML_CPP_DIR_BEST}" PARENT_SCOPE)
            set(${YAML_CPP_VERSION_IF_FOUND} ${YAML_CPP_VERSION_BEST} PARENT_SCOPE)
        else()
            message(VERBOSE "yaml-cpp found in ${MACE_PROJECT_3RDPARTY_DIR} (version: ${YAML_CPP_VERSION_BEST}), but does not reach the minimum requirement (${MACE_YAML_CPP_MINIMUM_REQUIRED})")
            set(${YAML_CPP_FOUND} FALSE PARENT_SCOPE)
            set(${YAML_CPP_DIR_IF_FOUND} "" PARENT_SCOPE)
            set(${YAML_CPP_VERSION_IF_FOUND} 0 PARENT_SCOPE)
        endif()
    endif()
endfunction()

include(${MACE_PROJECT_CMAKE_DIR}/DownloadSmallFile.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/UnpackSmallTar.cmake)

if(MACE_BUILTIN_YAML_CPP)
    message(STATUS "MACE will use built-in yaml-cpp")
    cmake_path(RELATIVE_PATH MACE_PROJECT_3RDPARTY_DIR BASE_DIRECTORY "${CMAKE_BINARY_DIR}"
               OUTPUT_VARIABLE MACE_PROJECT_3RDPARTY_DIR_RELATIVE)
    message(STATUS "Looking for yaml-cpp in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE}")
    # looking for yaml-cpp in MACE_PROJECT_3RDPARTY_DIR
    mace_find_built_in_yaml_cpp(MACE_BUILTIN_YAML_CPP_FOUND MACE_BUILTIN_YAML_CPP_DIR MACE_BUILTIN_YAML_CPP_VERSION)
    # if found in MACE_PROJECT_3RDPARTY_DIR, use it. otherwise download it
    if(NOT MACE_BUILTIN_YAML_CPP_FOUND)
        message(NOTICE "***Notice: yaml-cpp not found in directory of 3rd-party dependencies (minimum required is ${MACE_YAML_CPP_MINIMUM_REQUIRED}). It will be downloaded")
        # check download version
        if(MACE_DOWNLOAD_YAML_CPP_VERSION VERSION_LESS MACE_YAML_CPP_MINIMUM_REQUIRED)
            message(NOTICE "***Notice: Provided MACE_DOWNLOAD_YAML_CPP_VERSION is ${MACE_DOWNLOAD_YAML_CPP_VERSION}, which is less than the requirement (${MACE_YAML_CPP_MINIMUM_REQUIRED}). Changing to ${MACE_YAML_CPP_MINIMUM_REQUIRED}")
            set(MACE_DOWNLOAD_YAML_CPP_VERSION ${MACE_YAML_CPP_MINIMUM_REQUIRED})
        endif()
        # set download src and dest
        set(MACE_BUILTIN_YAML_CPP_ARCHIVE_SRC "https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-${MACE_DOWNLOAD_YAML_CPP_VERSION}.tar.gz")
        set(MACE_BUILTIN_YAML_CPP_ARCHIVE_DEST "${CMAKE_BINARY_DIR}/.cache/yaml-cpp-yaml-cpp-${MACE_DOWNLOAD_YAML_CPP_VERSION}.tar.gz")
        # download yaml-cpp
        message(STATUS "Downloading yaml-cpp archive")
        mace_download_small_file("${MACE_BUILTIN_YAML_CPP_ARCHIVE_SRC}" "${MACE_BUILTIN_YAML_CPP_ARCHIVE_DEST}")
        message(STATUS "Downloading yaml-cpp archive - done")
        # untar yaml-cpp
        message(STATUS "Unpacking yaml-cpp archive")
        mace_unpack_small_tar("${MACE_BUILTIN_YAML_CPP_ARCHIVE_DEST}" "${MACE_PROJECT_3RDPARTY_DIR}")
        message(STATUS "Unpacking yaml-cpp archive - done")
        # check again for safety
        mace_find_built_in_yaml_cpp(MACE_BUILTIN_YAML_CPP_FOUND MACE_BUILTIN_YAML_CPP_DIR MACE_BUILTIN_YAML_CPP_VERSION)
        if(NOT MACE_BUILTIN_YAML_CPP_FOUND)
            message(FATAL_ERROR "yaml-cpp still remains invalid, even after the download procedure. This may be caused by an incomplete download, or by a corrupted directory structure. If you encountered problem in downloading, you can manually download yaml-cpp from ${MACE_BUILTIN_YAML_CPP_ARCHIVE_SRC} and copy it to ${CMAKE_BINARY_DIR}/.cache (and keep the file name), or directly unpack it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree, delete all yaml-cpp-yaml-cpp-* directories under ${MACE_PROJECT_3RDPARTY_DIR}, then re-run CMake.")
        endif()
    endif()
    # report
    if(NOT DEFINED MACE_BUILTIN_YAML_CPP_ARCHIVE_SRC)
        message(STATUS "Looking for yaml-cpp in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE} - found (version: ${MACE_BUILTIN_YAML_CPP_VERSION})")
    else()
        message(STATUS "Looking for yaml-cpp in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE} - downloaded (version: ${MACE_BUILTIN_YAML_CPP_VERSION})")
    endif()
    # unset crap
    unset(MACE_BUILTIN_YAML_CPP_ARCHIVE_DEST)
    unset(MACE_BUILTIN_YAML_CPP_ARCHIVE_SRC)
    unset(MACE_PROJECT_3RDPARTY_DIR_RELATIVE)
    # configure yaml-cpp
    # include()
    # set env
    set(YAML_CPP_INCLUDE_DIR "${MACE_BUILTIN_YAML_CPP_DIR}/include")
    set(YAML_CPP_LIBRARIES yaml-cpp)
endif()

message(STATUS "MACE will use yaml-cpp headers from: ${YAML_CPP_INCLUDE_DIR}")
message(STATUS "MACE will use yaml-cpp libraries: ${YAML_CPP_LIBRARIES}")

if(NOT MACE_BUILTIN_YAML_CPP)
    message(STATUS "Looking for yaml-cpp - found (version: ${YAML_CPP_VERSION})")
else()
    message(STATUS "Looking for yaml-cpp - built-in (version: ${MACE_BUILTIN_YAML_CPP_VERSION})")
endif()
