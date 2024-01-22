#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"

#include "fmt/format.h"

namespace MACE::inline Extension::MPIX {

auto ParallelizePathInPlace(std::filesystem::path& path) -> void {
    const auto extension{path.extension().generic_string()};
    ParallelizePathInPlace(path.replace_extension(), extension);
}

auto ParallelizePathInPlace(std::filesystem::path& path, std::string_view extension) -> void {
    // file name without extension
    auto fileName{path.filename()};
    if (fileName.empty()) {
        throw std::logic_error("MACE::Utility::MPIX::ParallelizePathInPlace: Empty name");
    }

    if (const auto& mpiEnv{Env::MPIEnv::Instance()};
        mpiEnv.Parallel()) {
        // root directory
        if (mpiEnv.OnCluster()) {
            path /= mpiEnv.LocalNode().name;
        }
        // create root directory
        if (mpiEnv.OnCommNodeMaster()) {
            std::filesystem::create_directories(path);
        }
        // wait for create_directories
        MPI_Request mpiBarrierRequest;
        MPI_Ibarrier(mpiEnv.CommNode(),
                     &mpiBarrierRequest);
        // construct full path
        path /= fileName.concat(fmt::format(".mpi{}.", mpiEnv.CommWorldRank())).replace_extension(extension);
        // wait for create_directories
        MPI_Wait(&mpiBarrierRequest,
                 MPI_STATUS_IGNORE);
    } else {
        path.concat(".").replace_extension(extension);
    }
}

} // namespace MACE::inline Extension::MPIX
