#include "MACE/Utility/MPITool/MakeMPIFilePath.hxx"

#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

namespace MACE::Utility::MPITool {

std::filesystem::path MakeMPIFilePath(std::string_view basicName, std::string_view suffix, const MPI::Comm& comm) {
    constexpr int masterRank = 0;
    constexpr size_t maxProcessorName = MPI_MAX_PROCESSOR_NAME;
#ifdef PATH_MAX
    constexpr size_t pathMax = PATH_MAX;
#else
    constexpr size_t pathMax = 4096;
#endif

    auto ConstructPathInMPIExecution = [&]() -> std::filesystem::path {
        const auto commRank = comm.Get_rank();
        const auto commSize = comm.Get_size();

        // First: gather processor names

        // each rank get its processor name and length
        char processorNameSend[maxProcessorName];
        int processorNameLength;
        MPI::Get_processor_name(processorNameSend, processorNameLength);

        // master rank collects processor names
        std::vector<std::array<char, maxProcessorName>> processorNamesRecv;
        if (commRank == masterRank) { processorNamesRecv.resize(commSize); }
        comm.Gather(processorNameSend, maxProcessorName, MPI::CHAR, processorNamesRecv.data(), maxProcessorName, MPI::CHAR, masterRank);

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
                std::string fileName;
                std::stringstream ss;
                ss << basicName << "_rank" << rank << suffix;
                ss >> fileName;
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
        comm.Scatter(filePathsSend.data(), pathMax, MPI::CHAR, filePathRecv, pathMax, MPI::CHAR, masterRank);

        return filePathRecv;
    };

    auto ConstructPathInSerialExecution = [&]() -> std::filesystem::path {
        return std::string(basicName).append(suffix);
    };

    if (MPI::Is_initialized()) {
        if (comm.Get_size() > 1) {
            return ConstructPathInMPIExecution();
        } else {
            return ConstructPathInSerialExecution();
        }
    } else {
        return ConstructPathInSerialExecution();
    }
}

} // namespace MACE::Utility::MPITool
