#pragma once

#include "mpi.h"

#include <filesystem>
#include <string_view>

namespace MACE::Utility::UtilMPI {

/// Create directories and file paths to help managing files during mpi processing.
///
/// For example:
///
/// An executable xxx do something like this:
///
///   MPI_Init(argc, argv);
///     ...
///   auto filePath = MACE::Utility::MPIUtil::MakeMPIFilePath("result", ".root");
///   SomeFileHandler::Open(filePath);
///     ...
///
/// When running xxx on 16 nodes (e.g. named as node0, ..., node15), each node has 24 processes :
/// A directory named result will be created, under which a series of directories named
/// node0, node1, ..., node15 will be created. And there will be a series of files named
/// result_rank0.root, ..., result_rank23.root under result/node0, etc. And a dirmap saves paths.
/// Directory structure as:
///
/// result ┬ node0 ┬ result_rank0.root
///        │       ├ result_rank1.root
///        │       ├ ...
///        │       └ result_rank23.root
///        ├ node1 ┬ result_rank24.root
///        │       ├ result_rank25.root
///        │       ├ ...
///        │       └ result_rank47.root
///        ├ ...
///        └ node15 ┬ result_rank360.root
///                 ├ result_rank361.root
///                 ├ ...
///                 └ result_rank383.root
///
/// When running xxx on 1 node (e.g. PC), which has 8 processes :
/// A directory named result will be created, under which a series of files named
/// result_rank0.root, ..., result_rank7.root will be created. And a dirmap saves directory path.
/// Directory structure as:
///
/// result ┬ result_rank0.root
///        ├ result_rank1.root
///        ├ ...
///        └ result_rank7.root
///
/// When just ./xxx (not in MPI mode) :
/// Just a single result.root will be created.
///
std::filesystem::path MakeMPIFilePath(std::string_view basicName, std::string_view suffix, MPI_Comm comm = MPI_COMM_WORLD);

} // namespace MACE::Utility::MPIUtil
