#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <fstream>
#include <set>
#include <thread>
#include <vector>

#include "MPITools/MPIFileTools.hxx"

using namespace MACE::Utility;

ObserverPtr<std::ostream> MPIFileTools::fgOut = std::addressof(std::cout);

MPIFileTools::MPIFileTools(std::string_view basicName, std::string_view suffix, const MPI::Comm& comm) :
    fBasicName(basicName),
    fSuffix(suffix),
    fComm(std::addressof(comm)),
    fFilePath() {
    if (MPI::Is_initialized()) {
        if (fComm->Get_size() > 1) {
            ConstructPathMPIImpl();
        } else {
            ConstructPathSerialImpl();
        }
    } else {
        ConstructPathSerialImpl();
    }
}

int MPIFileTools::MergeRootFiles(bool forced) const {
    if (MPI::Is_initialized()) {
        if (fComm->Get_size() > 1) {
            return MergeRootFilesMPIImpl(forced);
        } else {
            return MergeRootFilesSerialImpl();
        }
    } else {
        return MergeRootFilesSerialImpl();
    }
}

int MPIFileTools::MergeRootFilesViaFilesMap(std::string basicName, bool forced, const MPI::Comm& comm) {
    int commRank = fgMasterRank;
    if (MPI::Is_initialized()) {
        commRank = comm.Get_rank();
    }

    int retVal = 0;
    if (commRank == fgMasterRank) {
        std::filesystem::path basicPath(basicName);
        // file map
        std::ifstream fileMapIn(basicPath / (basicName + ".filesmap"), std::ios::in);
        // if not exists, skipped
        if (not fileMapIn.is_open()) {
            return 1;
        }
        // skip first 2 lines (annotations)
        fileMapIn.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        fileMapIn.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // file paths read
        std::vector<std::filesystem::path> filePathList;
        // read paths
        while (not fileMapIn.eof()) {
            std::filesystem::path thisPath;
            fileMapIn >> thisPath;
            if (thisPath.extension() == ".root") {
                filePathList.emplace_back(thisPath);
            }
        }
        // if not root, skipped
        if (filePathList.empty()) {
            return 1;
        }
        // files to be merged
        const auto fileCount = filePathList.size();

        *fgOut << "Rank" << fgMasterRank << " is merging root files via hadd." << std::endl;
        // hadd command
        std::string command = "hadd ";
        // flag: -j
        const unsigned int hardwareMax = std::thread::hardware_concurrency();
        const unsigned int haddRequire = std::ceil(double(fileCount) / 5);
        const auto haddProcesses = std::min(hardwareMax, haddRequire);
        if (haddProcesses > 1) {
            command += ("-j " + std::to_string(haddProcesses) + ' ');
        }
        // flag: -f
        if (forced) { command += "-f "; }
        // TARGET
        command += (basicName + ".root");
        // SOURCE
        for (auto&& filePath : std::as_const(filePathList)) {
            command += ' ';
            command += filePath.string();
        }
        // do hadd
        retVal = std::system(command.c_str());
        // check hadd return value
        if (retVal == 0) {
            *fgOut << "Files merged successfully." << std::endl;
        } else {
            *fgOut << "Warning: Detected that hadd is returning non-zero value: " << retVal << "\n"
                   << "\tPlease check the infomation provided by hadd.\n"
                   << "\tMerge result might be corrupted, you could try to merge again.\n"
                   << "\t(Maybe you need to force re-creation of output? Can be done by passing argument <true>.)"
                   << std::endl;
        }
    }

    return retVal;
}

void MPIFileTools::ConstructPathMPIImpl() {
    const auto commRank = fComm->Get_rank();
    const auto commSize = fComm->Get_size();

    // First: gather processor names

    // each rank get its processor name and length
    char processorNameSend[fgProcessorNameMax];
    int processorNameLength;
    MPI::Get_processor_name(processorNameSend, processorNameLength);

    // master rank collects processor names
    std::vector<std::array<char, fgProcessorNameMax>> processorNamesRecv(0);
    if (commRank == fgMasterRank) { processorNamesRecv.resize(commSize); }
    fComm->Gather(processorNameSend, fgProcessorNameMax, MPI::CHAR, processorNamesRecv.data(), fgProcessorNameMax, MPI::CHAR, fgMasterRank);

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
        const std::filesystem::path rootPath(fBasicName);
        std::vector<std::filesystem::path> directoryList(0);
        std::vector<std::filesystem::path> filePathList(0);
        filePathList.reserve(commSize);
        if (processorNameSet.size() > 1) { // is running on cluster or supercomputer!
            // construct directory names
            directoryList.reserve(processorNameSet.size());
            for (auto&& uniqueProcessorName : std::as_const(processorNameSet)) {
                directoryList.emplace_back(rootPath / uniqueProcessorName);
            }
            // construct full file paths
            for (int rank = 0; rank < commSize; ++rank) {
                filePathList.emplace_back(rootPath / std::as_const(processorNameList[rank]) / FileNameForRank(rank));
            }
        } else { // is running on work station!
            // construct directory names
            directoryList.emplace_back(fBasicName);
            // construct full file paths
            for (int rank = 0; rank < commSize; ++rank) {
                filePathList.emplace_back(rootPath / FileNameForRank(rank));
            }
        }

        // create directories
        for (auto&& directory : std::as_const(directoryList)) {
            std::filesystem::create_directories(directory);
        }

        // save files map
        std::ofstream fileMapOut(rootPath / (fBasicName + ".filesmap"), std::ios::out);
        fileMapOut << "# DO NOT EDIT.\n"
                      "# Auto generated by MACE::MPITools::MPIFileTools.\n";
        for (auto&& filePath : std::as_const(filePathList)) {
            fileMapOut << filePath << '\n';
        }
        fileMapOut << std::flush;
        fileMapOut.close();

        // construct file path to be sent
        filePathsSend.reserve(commSize);
        for (auto&& filePath : std::as_const(filePathList)) {
            auto& filePathSend = filePathsSend.emplace_back();
            std::strcpy(filePathSend.data(), filePath.c_str());
        }
    }

    // Third: Scatter file paths

    char filePathRecv[fgFilePathMax];
    fComm->Scatter(filePathsSend.data(), fgFilePathMax, MPI::CHAR, filePathRecv, fgFilePathMax, MPI::CHAR, fgMasterRank);

    fFilePath = filePathRecv;
}

int MPIFileTools::MergeRootFilesMPIImpl(bool forced) const {
    const auto commRank = fComm->Get_rank();
    const auto commSize = fComm->Get_size();

    if (fSuffix != ".root") {
        if (commRank == fgMasterRank) { ReportSuffixNotRoot(); }
        return -1;
    }

    // gather file paths

    char filePathSend[fgFilePathMax];
    std::strcpy(filePathSend, fFilePath.c_str());

    std::vector<std::array<char, fgFilePathMax>> filePathsRecv(0);
    if (commRank == fgMasterRank) { filePathsRecv.resize(commSize); }
    fComm->Gather(filePathSend, fgFilePathMax, MPI::CHAR, filePathsRecv.data(), fgFilePathMax, MPI::CHAR, fgMasterRank);

    int retVal;
    if (commRank == fgMasterRank) {
        *fgOut << "Rank" << fgMasterRank << " is merging root files via hadd." << std::endl;
        // hadd command
        std::string command = "hadd ";
        // flag: -j
        const unsigned int hardwareMax = std::thread::hardware_concurrency();
        const unsigned int haddRequire = std::ceil(double(commSize) / 5.0);
        const auto haddProcesses = std::min(hardwareMax, haddRequire);
        if (haddProcesses > 1) {
            command += ("-j " + std::to_string(haddProcesses) + ' ');
        }
        // flag: -f
        if (forced) { command += "-f "; }
        // TARGET
        command += (fBasicName + fSuffix);
        // SOURCE
        for (auto&& filePath : std::as_const(filePathsRecv)) {
            command += ' ';
            command += filePath.data();
        }
        // do hadd
        retVal = std::system(command.c_str());
        // check hadd return value
        if (retVal == 0) {
            *fgOut << "Files merged successfully." << std::endl;
        } else {
            *fgOut << "Warning: Detected that hadd is returning non-zero value: " << retVal << "\n"
                   << "\tPlease check the infomation provided by hadd.\n"
                   << "\tMerge result might be corrupted, you could try to merge again.\n"
                   << "\t(Maybe you need to force re-creation of output? Can be done by passing argument <true>.)"
                   << std::endl;
        }
    }

    fComm->Bcast(std::addressof(retVal), 1, MPI::INT, fgMasterRank);
    return retVal;
}

int MPIFileTools::MergeRootFilesSerialImpl() const {
    if (fSuffix != ".root") {
        ReportSuffixNotRoot();
        return -1;
    }
    *fgOut << "Need not to merge files in serial execution. Skipped." << std::endl;
    return 0;
}

void MPIFileTools::ReportSuffixNotRoot() const {
    *fgOut << "Warning: MACE::MPIFileTools::MergeRootFiles() only supports merging root files with suffix <.root>.\n"
           << "\t<" << fSuffix << "> files are not supported. Nothing was done." << std::endl;
}
