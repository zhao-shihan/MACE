function(mace_download_small_file SRC_URL DEST_PATH)
    # check param
    if(NOT IS_ABSOLUTE "${DEST_PATH}")
        message(FATAL_ERROR "Parameter DEST_PATH needs to be an absolute path. (Current value: ${DEST_PATH})")
    endif()
    if(IS_DIRECTORY "${DEST_PATH}")
        message(FATAL_ERROR "Parameter DEST_PATH cannot be a directory. (Current value: ${DEST_PATH})")
    endif()
    # extract parent and name
    cmake_path(GET DEST_PATH PARENT_PATH DEST_DIR)
    cmake_path(GET DEST_PATH FILENAME DEST_NAME)
    # mkdir
    make_directory("${DEST_DIR}")
    if(NOT IS_DIRECTORY "${DEST_DIR}")
        message(FATAL_ERROR "The parent path of DEST_PATH (${DEST_DIR}) is not a directory.")
    endif()
    # request header
    message(STATUS "Requesting header (curl --no-progress-meter --retry 3 -ILo \"${DEST_NAME}.head\" \"${SRC_URL}\")")
    execute_process(COMMAND curl --no-progress-meter --retry 3 -ILo "${DEST_NAME}.head" "${SRC_URL}"
                    WORKING_DIRECTORY "${DEST_DIR}"
                    RESULT_VARIABLE DOWNLOAD_RETURN)
    # check return
    if(${DOWNLOAD_RETURN} EQUAL 0)
        file(REMOVE "${DEST_PATH}.head")
        # download w/ -C -
        message(STATUS "Downloading ${SRC_URL} to ${DEST_DIR} (curl --retry 3 -C - -Lo \"${DEST_NAME}\" \"${SRC_URL}\")")
        execute_process(COMMAND curl --retry 3 -C - -Lo "${DEST_NAME}" "${SRC_URL}"
                        WORKING_DIRECTORY "${DEST_DIR}"
                        RESULT_VARIABLE DOWNLOAD_RETURN)
        # check return
        if(NOT ${DOWNLOAD_RETURN} EQUAL 0)
            # download w/o -C -
            message(STATUS "Retrying without option \"-C -\"")
            execute_process(COMMAND curl --retry 3 -Lo "${DEST_NAME}" "${SRC_URL}"
                        WORKING_DIRECTORY "${DEST_DIR}"
                        RESULT_VARIABLE DOWNLOAD_RETURN)
        endif()
    endif()
    if(${DOWNLOAD_RETURN} EQUAL 0)
        message(STATUS "Download complete")
    else()
        message(SEND_ERROR "Failed to download ${SRC_URL} to ${DEST_DIR}, error: ${DOWNLOAD_RETURN}")
    endif()
endfunction()
