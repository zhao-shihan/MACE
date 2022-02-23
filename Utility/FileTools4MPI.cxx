#include <array>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
#include <iostream>

#include "Utility/FileTools4MPI.hxx"

using namespace MACE::Utility;

FileTools4MPI::FileTools4MPI(std::string_view basicName, std::string_view suffix) :
    fBasicName(basicName),
    fSuffix(suffix),
    fFilePath() {

    if (MPI::Is_initialized()) {
        MPI::Nullcomm comm(MPI_COMM_WORLD);
        const auto commRank = comm.Get_rank();
        const auto commSize = comm.Get_size();

        // First: gather processor names

        // each rank get its processor name and length
        char processorNameSend[fgProcessorNameMax];
        int processorNameLength;
        MPI::Get_processor_name(processorNameSend, processorNameLength);

        // master rank collects processor names
        std::vector<std::array<char, fgProcessorNameMax>> processorNamesRecv(0);
        if (commRank == fgMasterRank) { processorNamesRecv.resize(commSize); }
        comm.Gather(processorNameSend, fgProcessorNameMax, MPI_CHAR, processorNamesRecv.data(), fgProcessorNameMax, MPI_CHAR, fgMasterRank);

        std::vector<std::array<char, fgFilePathMax>> filePathsSend(0);
        if (commRank == fgMasterRank) {
            // master rank converts recieved char array to std::string_view
            std::vector<std::string_view> processorNameList(0);
            processorNameList.reserve(commSize);
            for (auto&& processorNameData : std::as_const(processorNamesRecv)) {
                processorNameList.emplace_back(processorNameData.data());
            }

            // find all unique processor names
            std::set<std::string_view> processorNameSet;
            for (auto&& processorName : std::as_const(processorNameList)) {
                processorNameSet.emplace(processorName);
            }

            // Second: create directories, construct and send full file paths

            auto FileNameForRank = [this](int rank) {
                std::string fileName;
                std::stringstream ss;
                ss << fBasicName << "_rank" << rank << fSuffix;
                ss >> fileName;
                return fileName;
            };

            // construct directory paths and full file paths
            std::vector<std::filesystem::path> directoryList(0);
            std::vector<std::filesystem::path> filePathList(0);
            filePathList.reserve(commSize);
            if (processorNameSet.size() > 1) { // is running on cluster or supercomputer!
                // construct directory names
                directoryList.reserve(processorNameSet.size());
                for (auto&& uniqueProcessorName : std::as_const(processorNameSet)) {
                    directoryList.emplace_back(std::filesystem::path(fBasicName) / uniqueProcessorName);
                }
                // construct full file paths
                for (size_t rank = 0; rank < commSize; ++rank) {
                    filePathList.emplace_back(std::filesystem::path(fBasicName) / std::as_const(processorNameList[rank]) / FileNameForRank(rank));
                }
            } else { // is running on work station!
                // construct directory names
                directoryList.emplace_back(fBasicName);
                // construct full file paths
                for (size_t rank = 0; rank < commSize; ++rank) {
                    filePathList.emplace_back(std::filesystem::path(fBasicName) / FileNameForRank(rank));
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

        char filePathRecv[fgFilePathMax];
        comm.Scatter(filePathsSend.data(), fgFilePathMax, MPI_CHAR, filePathRecv, fgFilePathMax, MPI_CHAR, fgMasterRank);

        fFilePath = filePathRecv;

    } else { // MPI is not initialized
        fFilePath = fBasicName + fSuffix;
    }
}

int FileTools4MPI::MergeRootFiles(bool forced) {
    auto ReportNotRoot = [this]() {
        std::cout << "Warning: MACE::Utility::FileTools4MPI::MergeRootFiles() only supports merging root files, "
            "with suffix <.root>. <" << fSuffix << "> files are not supported. Nothing was done." << std::endl;
    };

    if (MPI::Is_initialized()) {
        MPI::Nullcomm comm(MPI_COMM_WORLD);
        const auto commRank = comm.Get_rank();
        const auto commSize = comm.Get_size();

        if (fSuffix != ".root") {
            if (commRank == fgMasterRank) { ReportNotRoot(); }
            return -1;
        }

        // gather file paths

        char filePathSend[fgFilePathMax];
        std::strcpy(filePathSend, fFilePath.c_str());

        std::vector<std::array<char, fgFilePathMax>> filePathsRecv(0);
        if (commRank == fgMasterRank) { filePathsRecv.resize(commSize); }
        comm.Gather(filePathSend, fgFilePathMax, MPI_CHAR, filePathsRecv.data(), fgFilePathMax, MPI_CHAR, fgMasterRank);

        int retVal;
        if (commRank == fgMasterRank) {
            std::string command = "hadd ";
            if (forced) { command += "-f "; }
            command += (fBasicName + fSuffix);
            for (auto&& filePath : std::as_const(filePathsRecv)) {
                command += ' ';
                command += filePath.data();
            }
            std::cout << "rank" << fgMasterRank << " >\n";
            retVal = std::system(command.c_str());
            std::cout << std::endl;
        }

        comm.Bcast(std::addressof(retVal), 1, MPI_INT, fgMasterRank);
        return retVal;

    } else { // MPI is not initialized
        if (fSuffix != ".root") {
            ReportNotRoot();
            return -1;
        }
        return 0;
    }
}
