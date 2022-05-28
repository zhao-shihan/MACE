#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

namespace MACE::Utility::MPIUtil {

std::filesystem::path MakeMPIFilePath(std::string_view basicName, std::string_view suffix, MPI_Comm comm) {
    constexpr int masterRank = 0;
    constexpr size_t maxProcessorName = MPI_MAX_PROCESSOR_NAME;
#ifdef PATH_MAX
    constexpr size_t pathMax = PATH_MAX;
#else
    constexpr size_t pathMax = 4096;
#endif
    const auto commSize = MPICommSize(comm);

    if (commSize == 1) {

        return std::string(basicName).append(suffix);

    } else {

        const auto commRank = MPICommRank(comm);

        // First: gather processor names

        // each rank get its processor name
        const auto processorNameSend = MPIGetProcessorName<maxProcessorName>().first;

        // master rank collects processor names
        std::vector<std::array<char, maxProcessorName>> processorNamesRecv;
        if (commRank == masterRank) { processorNamesRecv.resize(commSize); }
        MPI_Gather(processorNameSend.data(), maxProcessorName, MPI_CHAR, processorNamesRecv.data(), maxProcessorName, MPI_CHAR, masterRank, comm);

        std::vector<std::array<char, pathMax>> filePathsSend;
        if (commRank == masterRank) {
            // master rank converts recieved char array to std::string_view
            std::vector<std::string_view> processorNameList;
            processorNameList.reserve(commSize);
            for (auto&& processorNameData : std::as_const(processorNamesRecv)) {
                processorNameList.emplace_back(processorNameData.data());
            }

            // find all unique processor names
            std::set<std::string_view> processorNameSet;
            for (auto&& processorName : std::as_const(processorNameList)) {
                processorNameSet.emplace(processorName);
            }

            // Second: create directories, construct full file paths

            auto FileNameForRank = [&](int rank) {
                std::string fileName(basicName);
                fileName.append("_rank").append(std::to_string(rank)).append(suffix);
                return fileName;
            };

            // construct directory paths and full file paths
            const std::filesystem::path rootPath(basicName);
            std::vector<std::filesystem::path> directoryList;
            std::vector<std::filesystem::path> filePathList;
            filePathList.reserve(commSize);
            if (processorNameSet.size() == 1) { // running on work station!
                // construct directory names
                directoryList.emplace_back(basicName);
                // construct full file paths
                for (int rank = 0; rank < commSize; ++rank) {
                    filePathList.emplace_back(rootPath / FileNameForRank(rank));
                }
            } else { // running on cluster!
                // construct directory names
                directoryList.reserve(processorNameSet.size());
                for (auto&& uniqueProcessorName : std::as_const(processorNameSet)) {
                    directoryList.emplace_back(rootPath / uniqueProcessorName);
                }
                // construct full file paths
                for (int rank = 0; rank < commSize; ++rank) {
                    filePathList.emplace_back(rootPath / std::as_const(processorNameList[rank]) / FileNameForRank(rank));
                }
            }

            // create directories
            for (auto&& directory : std::as_const(directoryList)) {
                std::filesystem::create_directories(directory);
            }

            // construct file path to be sent
            filePathsSend.reserve(commSize);
            for (auto&& filePath : std::as_const(filePathList)) {
                auto& filePathSend = filePathsSend.emplace_back();
                std::strcpy(filePathSend.data(), filePath.c_str());
            }
        }

        // Third: Scatter file paths

        char filePathRecv[pathMax];
        MPI_Scatter(filePathsSend.data(), pathMax, MPI_CHAR, filePathRecv, pathMax, MPI_CHAR, masterRank, comm);

        return std::filesystem::path(filePathRecv);
    }
}

} // namespace MACE::Utility::MPIUtil
