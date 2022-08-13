#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICall.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

namespace MACE::Utility::MPIUtil {

void MakeMPIFilePathInPlace(std::filesystem::path& path) {
    const auto extension = path.extension().generic_string();
    MakeMPIFilePathInPlace(path.replace_extension(), extension);
}

void MakeMPIFilePathInPlace(std::filesystem::path& path, std::string_view extension) {
    // file name without extension
    auto fileName = path.filename();
    if (fileName.empty()) {
        throw std::logic_error("MACE::Utility::MPIUtil::MakeMPIFilePathInPlace: Empty name");
    }

    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.IsParallel()) {
        // root directory
        if (mpiEnv.OnCluster()) {
            path /= mpiEnv.GetNodeName();
        }
        // create root directory
        if (mpiEnv.IsNodeMaster()) {
            std::filesystem::create_directories(path);
        }
        // construct full path
        path /= fileName.concat(".rank")
                    .concat(std::to_string(mpiEnv.GetWorldRank()))
                    .concat(extension);
        // wait for create_directories
        MACE_CHECKED_MPI_CALL(MPI_Barrier,
                              mpiEnv.GetNodeComm());
    } else {
        path.concat(extension);
    }
}

} // namespace MACE::Utility::MPIUtil
