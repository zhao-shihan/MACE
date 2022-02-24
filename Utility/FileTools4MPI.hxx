#include <string_view>
#include <filesystem>
#include <iostream>

#include "mpi.h"

#include "MACEGlobal.hxx"
#include "Utility/ObserverPtr.hxx"

// Create directories and file paths to help managing files during mpi processing.
//
// For example:
//
// An executable xxx will create a single result file, which do something like this:
//
//   MPI::Init(...);
//   ...
//   FileTools4MPI mpiFileTools("result", ".root");
//   SomeFileHandler::Open(mpiFileTools.GetFilePath());
//   ... (do some work, could be MPI parallely)
//   SomeFileHandler::Close();
//   mpiFileTools.MergeRootFiles()
//
// When running xxx on 16 nodes (e.g. named as node0, ..., node15), each node has 24 processes :
// A folder named result will be created, under which a series of folders named
// node0, node1, ..., node15 will be created. And there will be a series of files named
// result_rank0.root, ..., result_rank23.root under result/node0, etc.
// Directory structure as:
//
// result ┬ node0 ┬ result_rank0.root
//        │       ├ result_rank1.root
//        │       ├ ...
//        │       └ result_rank23.root
//        ├ node1 ┬ result_rank24.root
//        │       ├ result_rank25.root
//        │       ├ ...
//        │       └ result_rank47.root
//        ├ ...
//        └ node15 ┬ result_rank360.root
//                 ├ result_rank361.root
//                 ├ ...
//                 └ result_rank383.root
// xxx
// result.root                                      -> (created by MergeRootFiles())
//
// When running xxx on 1 node (e.g. PC), which has 8 processes :
// A folder named result will be created, under which a series of files named
// result_rank0.root, ..., result_rank7.root will be created.
// Directory structure as:
//
// result ┬ result_rank0.root
//        ├ result_rank1.root
//        ├ ...
//        └ result_rank7.root
// xxx
// result.root                                      -> (created by MergeRootFiles())
//
// When just ./xxx (not in MPI mode) : 
// Just a single result.root will be created.
//
class MACE::Utility::FileTools4MPI final {
public:
    FileTools4MPI(std::string_view basicName, std::string_view suffix, const MPI::Comm& comm = MPI::COMM_WORLD);
    ~FileTools4MPI() noexcept = default;
    FileTools4MPI(const FileTools4MPI&) = delete;
    FileTools4MPI& operator=(const FileTools4MPI&) = delete;

    [[nodiscard]] const auto& GetFilePath() const { return fFilePath; }
    int MergeRootFiles(bool forced = false) const;

    static void SetOutStream(std::ostream& os) { fgOut = std::addressof(os); }

private:
    void ConstructPathMPIImpl();
    void ConstructPathSerialImpl() { fFilePath = fBasicName + fSuffix; }

    [[nodiscard]] int MergeRootFilesMPIImpl(bool forced) const;
    [[nodiscard]] int MergeRootFilesSerialImpl() const;
    void ReportSuffixNotRoot() const;

private:
    const std::string                  fBasicName;
    const std::string                  fSuffix;
    const ObserverPtr<const MPI::Comm> fComm;

    std::filesystem::path              fFilePath;

    static constexpr int               fgMasterRank = 0;
    static constexpr int               fgProcessorNameMax = MPI_MAX_PROCESSOR_NAME;
    static constexpr int               fgFilePathMax = 4 * MPI_MAX_PROCESSOR_NAME;

    static ObserverPtr<std::ostream>   fgOut;
};
