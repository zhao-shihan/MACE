message(STATUS "Looking for MPI_C")

find_package(MPI 2.0 REQUIRED C)

message(STATUS "MACE will use MPI_C headers from: ${MPI_C_INCLUDE_DIRS}")
message(STATUS "MACE will use MPI_C libraries: ${MPI_C_LIBRARIES}")

message(STATUS "Looking for MPI_C - found (version: ${MPI_C_VERSION})")
