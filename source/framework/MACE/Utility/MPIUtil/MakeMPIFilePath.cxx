#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include <array>
#include <climits>
#include <cstring>
#include <set>
#include <vector>

namespace MACE::Utility::MPIUtil {

std::filesystem::path MakeMPIFilePath(std::string_view basicName, std::string_view suffix, MPI_Comm comm) {
#ifdef PATH_MAX
    constexpr size_t pathMax = PATH_MAX; // Unix
#elif defined(_MAX_PATH)
    constexpr size_t pathMax = _MAX_PATH; // Windows
#else
    constexpr size_t pathMax = 260; // ???
#endif

    using Environment::MPIEnvironment;

    if (MPIEnvironment::IsSerialized()) {

        return std::string(basicName).append(suffix);

    } else { // Parallel

        // First: gather processor names

        // each rank get its processor name
        const auto processorNameSend = MPIEnvironment::ProcessorName().c_str();

        // master rank collects processor names
        std::vector<std::array<char, MPI_MAX_PROCESSOR_NAME>> processorNamesRecv;
        if (MPIEnvironment::IsWorldMaster()) { processorNamesRecv.resize(MPIEnvironment::WorldCommSize()); }
        MPI_Gather(processorNameSend, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, processorNamesRecv.data(), MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, comm);

        std::vector<std::array<char, pathMax>> filePathsSend;
        if (MPIEnvironment::IsWorldMaster()) {
            // find all unique processor names
            std::set<std::string_view> processorNameSet;
            for (auto&& processorName : std::as_const(processorNamesRecv)) {
                processorNameSet.emplace(processorName.data());
            }

            // Second: create directories, construct full file paths

            auto FileNameOfRank = [&](int rank) {
                std::string fileName(basicName);
                fileName.append("_rank").append(std::to_string(rank)).append(suffix);
                return fileName;
            };

            // construct directory paths and full file paths
            const std::filesystem::path rootPath(basicName);
            std::vector<std::filesystem::path> directoryList;
            std::vector<std::filesystem::path> filePathList;
            filePathList.reserve(MPIEnvironment::WorldCommSize());
            if (processorNameSet.size() == 1) { // running on work station!
                // construct directory names
                directoryList.emplace_back(basicName);
                // construct full file paths
                for (int rank = 0; rank < MPIEnvironment::WorldCommSize(); ++rank) {
                    filePathList.emplace_back(rootPath / FileNameOfRank(rank));
                }
            } else { // running on cluster!
                // construct directory names
                directoryList.reserve(processorNameSet.size());
                for (auto&& uniqueProcessorName : std::as_const(processorNameSet)) {
                    directoryList.emplace_back(rootPath / uniqueProcessorName);
                }
                // construct full file paths
                for (int rank = 0; rank < MPIEnvironment::WorldCommSize(); ++rank) {
                    filePathList.emplace_back(rootPath / std::as_const(processorNamesRecv)[rank].data() / FileNameOfRank(rank));
                }
            }

            // create directories
            for (auto&& directory : std::as_const(directoryList)) {
                std::filesystem::create_directories(directory);
            }

            // construct file path to be sent
            filePathsSend.reserve(MPIEnvironment::WorldCommSize());
            for (auto&& filePath : std::as_const(filePathList)) {
                auto& filePathSend = filePathsSend.emplace_back();
                std::strcpy(filePathSend.data(), filePath.generic_string().c_str());
            }
        }

        // Third: Scatter file paths

        char filePathRecv[pathMax];
        MPI_Scatter(std::as_const(filePathsSend).data(), pathMax, MPI_CHAR, filePathRecv, pathMax, MPI_CHAR, 0, comm);

        return std::filesystem::path(filePathRecv);
    }
}

} // namespace MACE::Utility::MPIUtil
