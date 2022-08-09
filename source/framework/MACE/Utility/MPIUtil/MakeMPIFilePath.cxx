#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include <filesystem>

namespace MACE::Utility::MPIUtil {

std::string MakeMPIFilePath(std::string_view basicName, std::string_view suffix) {
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.IsSequential()) {
        return std::string(basicName).append(suffix);
    } else {
        // root directory
        std::filesystem::path rootPath(basicName);
        if (mpiEnv.OnCluster()) {
            rootPath /= mpiEnv.NodeName();
        }
        // create root directory
        if (mpiEnv.IsNodeMaster()) {
            std::filesystem::create_directories(rootPath);
        }
        // file name
        const auto fileName = std::string(basicName)
                                  .append("_rank")
                                  .append(std::to_string(mpiEnv.WorldCommRank()))
                                  .append(suffix);
        return (rootPath / fileName).generic_string();
    }
}

} // namespace MACE::Utility::MPIUtil
