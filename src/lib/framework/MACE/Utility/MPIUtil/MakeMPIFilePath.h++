#pragma once

#include <concepts>
#include <filesystem>
#include <string_view>

namespace MACE::inline Utility::MPIUtil {

/// Create directories and file paths to help managing files during mpi processing.
///
/// For example:
///
/// An executable xxx do something like this:
///
///   MPI_Init(argc, argv);
///     ...
///   auto filePath = MACE::MPIUtil::MakeMPIFilePath("result.root");
///   // or, equivalently
///   // auto filePath = MACE::MPIUtil::MakeMPIFilePath("result", ".root");
///   SomeFileHandler::Open(filePath);
///     ...
///
/// When running xxx on 16 nodes (e.g. named as node0, ..., node15), each node has 24 processes:
/// A directory named result will be created, under which a series of directories named
/// node0, node1, ..., node15 will be created. And there will be a series of files named
/// result.rank0.root, ..., result.rank23.root under result/node0, etc. And a dirmap saves paths.
/// Directory structure as:
///
/// result ┬ node0 ┬ result.rank0.root
///        │       ├ result.rank1.root
///        │       ├ ...
///        │       └ result.rank23.root
///        ├ node1 ┬ result.rank24.root
///        │       ├ result.rank25.root
///        │       ├ ...
///        │       └ result.rank47.root
///        ├ ...
///        └ node15 ┬ result.rank360.root
///                 ├ result.rank361.root
///                 ├ ...
///                 └ result.rank383.root
///
/// When running xxx on 1 node (e.g. PC), which has 8 processes:
/// A directory named result will be created, under which a series of files named
/// result.rank0.root, ..., result.rank7.root will be created. And a dirmap saves directory path.
/// Directory structure as:
///
/// result ┬ result.rank0.root
///        ├ result.rank1.root
///        ├ ...
///        └ result.rank7.root
///
/// When just ./xxx (not in MPI mode) :
/// Just a single result.root will be created.
///
auto MakeMPIFilePath(std::convertible_to<std::filesystem::path> auto&& path) -> std::filesystem::path;
auto MakeMPIFilePath(std::convertible_to<std::filesystem::path> auto&& path, std::string_view extension) -> std::filesystem::path;
auto MakeMPIFilePathInPlace(std::filesystem::path& path) -> void;
auto MakeMPIFilePathInPlace(std::filesystem::path& path, std::string_view extension) -> void;

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/MakeMPIFilePath.inl"
