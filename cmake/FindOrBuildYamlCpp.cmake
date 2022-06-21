message(STATUS "Looking for yaml-cpp")

set(MACE_YAML_CPP_MINIMUM_REQUIRED 0.6.0)

if(NOT MACE_BUILTIN_YAML_CPP)
    find_package(yaml-cpp ${MACE_YAML_CPP_MINIMUM_REQUIRED} QUIET)
    if(NOT yaml-cpp_FOUND)
        message(NOTICE "***Notice: yaml-cpp not found (minimum required is ${MACE_YAML_CPP_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_YAML_CPP")
        set(MACE_BUILTIN_YAML_CPP ON)
    endif()
endif()

if(MACE_BUILTIN_YAML_CPP)
    message(STATUS "MACE will use built-in yaml-cpp")
    set(YAML_CPP_INCLUDE_DIR "${MACE_BUILTIN_YAML_CPP_DIR}/include")
    set(YAML_CPP_LIBRARIES yaml-cpp)
endif()

message(STATUS "MACE will use yaml-cpp headers from: ${YAML_CPP_INCLUDE_DIR}")
message(STATUS "MACE will use yaml-cpp libraries: ${YAML_CPP_LIBRARIES}")

if(NOT MACE_BUILTIN_YAML_CPP)
    message(STATUS "Looking for yaml-cpp - found (version: ${YAML_CPP_VERSION})")
else()
    message(STATUS "Looking for yaml-cpp - builtin")
endif()
