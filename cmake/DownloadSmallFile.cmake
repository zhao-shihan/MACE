function(mace_download_small_file SRC_URL DEST_PATH)
    # check param
    if(NOT IS_ABSOLUTE "${DEST_PATH}")
        message(FATAL_ERROR "Parameter DEST_PATH needs to be an absolute path. (Current value: ${DEST_PATH})")
    endif()
    if(IS_DIRECTORY "${DEST_PATH}")
        message(FATAL_ERROR "Parameter DEST_PATH cannot be a directory. (Current value: ${DEST_PATH})")
    endif()
    # skip if exist
    if(EXISTS "${DEST_PATH}")
        message(STATUS "Reusing ${DEST_PATH}, skpping download")
    else()
        # mkdir
        cmake_path(GET DEST_PATH PARENT_PATH DEST_DIR)
        make_directory("${DEST_DIR}")
        if(NOT IS_DIRECTORY "${DEST_DIR}")
            message(FATAL_ERROR "The parent path of DEST_PATH (${DEST_DIR}) is not a directory.")
        endif()
        # process curl
        message(STATUS "Executing command: curl -o \"${DEST_PATH}\" \"${SRC_URL}\"")
        execute_process(COMMAND "curl" "-o" "${DEST_PATH}" "${SRC_URL}"
                        RESULT_VARIABLE CURL_RETURN)
        # check return
        if(NOT ${CURL_RETURN} EQUAL 0)
            message(SEND_ERROR "Failed to download from ${SRC_URL} to ${DEST_PATH}")
        endif()
    endif()
endfunction()
