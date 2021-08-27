#include <map>
#include <fstream>

#include "Global.hh"
#include "Analysis.hh"
#include "RunManager.hh"

using namespace MACE::SimMTransport;

Global::~Global() {}

Global* Global::Instance() {
    static Global global;
    return &global;
}

static std::map<std::string, std::string> CFGReader(const char* cfgFileName);

void Global::Initialize(int& argc, char**& argv) {
    MPI_Init(&argc, &argv);

    int commRank; MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    int commSize; MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    if (commSize < 2 || argc < 2) {
        delete RunManager::Instance();
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    auto global = Global::Instance();

    global->SetCommRank(commRank);
    global->SetCommSize(commSize);
    global->SetMasterRank(commSize - 1);
    global->SetWorkerNum(commSize - 1);

    auto cfg = CFGReader(argv[1]);

    try {
        global->SetName(cfg.at("Name"));
        global->SetTarget(new TF3("Target", cfg.at("Target").c_str()));
        global->SetStepOfPushing(std::stod(cfg.at("StepOfPushing")));
        global->SetPeriodicBoundaryX(std::stod(cfg.at("PeriodicBoundaryX")));
        global->SetPeriodicBoundaryY(std::stod(cfg.at("PeriodicBoundaryY")));
        global->SetPeriodicBoundaryZ(std::stod(cfg.at("PeriodicBoundaryZ")));
        global->SetMuoniumLife(std::stod(cfg.at("MuoniumLife")));
        global->SetMuoniumMass(std::stod(cfg.at("MuoniumMass")));
        global->SetMeanFreePath(new TF3("MeanFreePath", cfg.at("MeanFreePath").c_str()));
        global->SetTemperature(std::stod(cfg.at("Temperature")));
        global->SetSource(new TF3("Source", cfg.at("Source").c_str(), std::stod(cfg.at("SourceXMin")), std::stod(cfg.at("SourceXMax")), std::stod(cfg.at("SourceYMin")), std::stod(cfg.at("SourceYMax")), std::stod(cfg.at("SourceZMin")), std::stod(cfg.at("SourceZMax"))));
        global->SetMuoniumNum(std::stoul(cfg.at("MuoniumNum")));
        global->SetBeginTime(std::stod(cfg.at("BeginTime")));
        global->SetOutputStep(std::stod(cfg.at("OutputStep")));
        global->SetEndTime(std::stod(cfg.at("EndTime")));
        global->SetSeedForWorker0(std::stoul(cfg.at("SeedForWorker0")));
        global->SetWorkerJobSize(std::stoul(cfg.at("WorkerJobSize")));
    } catch (std::out_of_range& err) {
        if (commRank == commSize - 1) {
            std::cerr << "Error: The config file " << argv[1] << " is incomplete. Aborting." << std::endl;
        }
        delete RunManager::Instance();
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    global->Source()->SetNpx(100);
    global->Source()->SetNpy(100);
    global->Source()->SetNpz(100);
}

void Global::Finalize() {
    MPI_Finalize();
}

static std::map<std::string, std::string> CFGReader(const char* cfgFileName) {
    std::map<std::string, std::string> cfgMap;
    std::ifstream fin(cfgFileName);
    if (!fin.is_open()) {
        int commRank; MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
        int commSize; MPI_Comm_size(MPI_COMM_WORLD, &commSize);
        if (commRank == commSize - 1) {
            std::cout << "Warning: Cannot open <" << cfgFileName << ">." << std::endl;
        }
        return cfgMap;
    }
    std::string line;
    while (!fin.eof()) {
        std::getline(fin, line);
        if (line.empty()) { continue; }  // Skip if empty.
        auto annotationPos = line.find_first_of('#');
        if (annotationPos != std::string::npos) {  // If there are annotation,
            line.erase(annotationPos); // drop annotation.
        }
        if (line.empty()) { continue; }  // Skip if there is only annotation.
        size_t spaceBeginPos, spaceEndPos;
        do { // drop all spaces.
            spaceBeginPos = line.find_first_of(' ');
            if (spaceBeginPos == std::string::npos) { break; }
            spaceEndPos = line.find_first_not_of(' ', spaceBeginPos);
            line.erase(spaceBeginPos, spaceEndPos - spaceBeginPos);
        } while (spaceEndPos != spaceBeginPos);
        if (line.empty()) { continue; }  // Skip if empty.
        auto eqPos = line.find_first_of('=');
        if (eqPos != line.find_last_of('=')) {
            std::cout << "Notice: Multiple = sign found in <" << cfgFileName << ">." << std::endl;
        }
        auto keySubStr = line.substr(0, eqPos);
        auto cfgSubStr = line.substr(eqPos + 1, line.find_first_of('=', eqPos) - (eqPos + 1));
        cfgMap.insert(std::make_pair(keySubStr, cfgSubStr));
    }
    fin.close();
    return cfgMap;
}
