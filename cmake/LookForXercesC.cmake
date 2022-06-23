message(STATUS "Looking for Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED}")

set(MACE_XERCES_C_EXACT_REQUIRED 3.2.3)

if(NOT MACE_BUILTIN_XERCES_C)
    find_package(XercesC ${MACE_XERCES_C_EXACT_REQUIRED} EXACT QUIET)
    if(NOT XercesC_FOUND)
        set(MACE_BUILTIN_XERCES_C ON)
        message(NOTICE "***Notice: Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} not found. Turning on MACE_BUILTIN_XERCES_C")
    endif()
endif()

# looking for Xerces-C++ in MACE_PROJECT_3RDPARTY_DIR
function(mace_find_built_in_xerces_c XERCES_C_FOUND XERCES_C_DIR_IF_FOUND)
    set(BUILTIN_XERCES_C_DIR "${MACE_PROJECT_3RDPARTY_DIR}/xerces-c-${MACE_XERCES_C_EXACT_REQUIRED}")
    # find possible Xerces-C++
    if(EXISTS "${BUILTIN_XERCES_C_DIR}/CMakeLists.txt" AND NOT IS_DIRECTORY "${BUILTIN_XERCES_C_DIR}/CMakeLists.txt")
        # found
        message(VERBOSE "Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} found in ${MACE_PROJECT_3RDPARTY_DIR}")
        set(${XERCES_C_FOUND} TRUE PARENT_SCOPE)
        set(${XERCES_C_DIR_IF_FOUND} "${BUILTIN_XERCES_C_DIR}" PARENT_SCOPE)
    else()
        # not found
        message(VERBOSE "Could not find Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} in ${MACE_PROJECT_3RDPARTY_DIR}")
        set(${XERCES_C_FOUND} FALSE PARENT_SCOPE)
        set(${XERCES_C_DIR_IF_FOUND} "" PARENT_SCOPE)
    endif()
endfunction()

include(${MACE_PROJECT_CMAKE_DIR}/ConfigureBuiltInXercesC.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/DownloadSmallFile.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/ExtractSmallTar.cmake)

if(MACE_BUILTIN_XERCES_C)
    message(STATUS "MACE will use built-in Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED}")
    cmake_path(RELATIVE_PATH MACE_PROJECT_3RDPARTY_DIR BASE_DIRECTORY "${CMAKE_BINARY_DIR}"
               OUTPUT_VARIABLE MACE_PROJECT_3RDPARTY_DIR_RELATIVE)
    message(STATUS "Looking for Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE}")
    # looking for Xerces-C++ in MACE_PROJECT_3RDPARTY_DIR
    mace_find_built_in_xerces_c(MACE_BUILTIN_XERCES_C_FOUND MACE_BUILTIN_XERCES_C_DIR)
    # if found in MACE_PROJECT_3RDPARTY_DIR, use it. otherwise download it
    if(NOT MACE_BUILTIN_XERCES_C_FOUND)
        message(NOTICE "***Notice: Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} not found in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE}. It will be downloaded")
        # set download src and dest
        set(MACE_BUILTIN_XERCES_C_ARCHIVE_SRC "https://dlcdn.apache.org/xerces/c/3/sources/xerces-c-${MACE_XERCES_C_EXACT_REQUIRED}.tar.xz")
        set(MACE_BUILTIN_XERCES_C_ARCHIVE_DEST "${CMAKE_BINARY_DIR}/.cache/xerces-c-${MACE_XERCES_C_EXACT_REQUIRED}.tar.xz")
        # download Xerces-C++
        message(STATUS "Downloading Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} archive")
        mace_download_small_file("${MACE_BUILTIN_XERCES_C_ARCHIVE_SRC}" "${MACE_BUILTIN_XERCES_C_ARCHIVE_DEST}")
        message(STATUS "Downloading Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} archive - done")
        # untar Xerces-C++
        message(STATUS "Extracting Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} archive")
        mace_extract_small_tar("${MACE_BUILTIN_XERCES_C_ARCHIVE_DEST}" "${MACE_PROJECT_3RDPARTY_DIR}")
        message(STATUS "Extracting Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} archive - done")
        # check again for safety
        mace_find_built_in_xerces_c(MACE_BUILTIN_XERCES_C_FOUND MACE_BUILTIN_XERCES_C_DIR)
        if(NOT MACE_BUILTIN_XERCES_C_FOUND)
            message(FATAL_ERROR "Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} still remains invalid, even after the download procedure. This may be caused by an incomplete download, or by a corrupted directory structure. If you encountered problem in downloading, you can manually download Xerces-C++ from ${MACE_BUILTIN_XERCES_C_ARCHIVE_SRC} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree, delete xerces-c-${MACE_XERCES_C_EXACT_REQUIRED} directory under ${MACE_PROJECT_3RDPARTY_DIR}, then re-run CMake.")
        endif()
    endif()
    # report
    if(NOT DEFINED MACE_BUILTIN_XERCES_C_ARCHIVE_SRC)
        message(STATUS "Looking for Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE} - found")
    else()
        message(STATUS "Looking for Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} in ${MACE_PROJECT_3RDPARTY_DIR_RELATIVE} - downloaded")
    endif()
    # unset crap
    unset(MACE_BUILTIN_XERCES_C_ARCHIVE_DEST)
    unset(MACE_BUILTIN_XERCES_C_ARCHIVE_SRC)
    unset(MACE_PROJECT_3RDPARTY_DIR_RELATIVE)
    # configure Xerces-C++
    mace_configure_built_in_xerces_c("${MACE_BUILTIN_XERCES_C_DIR}")
    # set env
    set(XercesC_INCLUDE_DIR "${MACE_BUILTIN_XERCES_C_DIR}/src")
    set(XercesC_LIBRARIES xerces-c)
endif()

message(STATUS "MACE will use Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} headers from: ${XercesC_INCLUDE_DIR}")
message(STATUS "MACE will use Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} libraries: ${XercesC_LIBRARIES}")

if(NOT MACE_BUILTIN_XERCES_C)
    message(STATUS "Looking for Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} - found")
else()
    message(STATUS "Looking for Xerces-C++ ${MACE_XERCES_C_EXACT_REQUIRED} - built-in")
endif()
