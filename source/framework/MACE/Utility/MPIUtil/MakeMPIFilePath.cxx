#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.hxx"

namespace MACE::inline Utility::MPIUtil {

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

    if (const auto& mpiEnv = Env::MPIEnv::Instance();
        mpiEnv.Parallel()) {
        // root directory
        if (mpiEnv.OnCluster()) {
            path /= mpiEnv.LocalHost().name;
        }
        // create root directory
        if (mpiEnv.AtLocalMaster()) {
            std::filesystem::create_directories(path);
        }
        // construct full path
        path /= fileName.concat(".rank")
                    .concat(std::to_string(mpiEnv.WorldCommRank()))
                    .concat(extension);
        // wait for create_directories
        MACE_MPI_CALL_WITH_CHECK(MPI_Barrier,
                                 mpiEnv.LocalComm())
    } else {
        path.concat(extension);
    }
}

} // namespace MACE::inline Utility::MPIUtil
