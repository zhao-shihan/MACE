#include <thread>

#include "RunManager.hh"
#include "Analysis.hh"

using namespace MACE::SimMTransport;

RunManager* RunManager::fInstance = nullptr;

RunManager* RunManager::Instance() {
    if (fInstance == nullptr) {
        fInstance = new RunManager();
    }
    return fInstance;
}

RunManager::RunManager() :
    fMaster(nullptr),
    fWorker(nullptr),
    fStatus(kRunUndefined) {}

RunManager::~RunManager() {}

#define MASTER_DO(statement) \
    if (gCommRank == gMasterRank) statement
#define WORKER_DO(statement) \
    else statement

void RunManager::Initialize(int* argc, char*** argv) {
    if (fStatus == kRunRunning || fStatus == kRunStopped) { return; }

    MPIGlobal::Initialize(argc, argv);

    MASTER_DO(fMaster = new Master());
    WORKER_DO(fWorker = new Worker());

    InitialReport();
    // ToDo: check gMeanFreePath grad.

    MASTER_DO(fMaster->Initialize());
    WORKER_DO(fWorker->Initialize());

    fStatus = kRunInitialized;
}

void RunManager::Run() {
    if (fStatus == kRunUndefined || fStatus == kRunFinalized) { return; }
    fStatus = kRunRunning;

    MASTER_DO(fMaster->Run());
    WORKER_DO(fWorker->Run());

    fStatus = kRunStopped;
}

void RunManager::Finalize() {
    if (fStatus != kRunStopped) { return; }

    MASTER_DO(fMaster->Finalize());
    WORKER_DO(fWorker->Finalize());

    FinalReport();

    MASTER_DO(delete fMaster);
    WORKER_DO(delete fWorker);

    MPIGlobal::Finalize();

    fStatus = kRunFinalized;
}

void RunManager::InitialReport() const {
    if (fStatus == kRunRunning || fStatus == kRunStopped) { return; }

    char processorName[MPI_MAX_PROCESSOR_NAME]; int processorNameLen;
    MPI_Get_processor_name(processorName, &processorNameLen);

    MPI_Barrier(MPI_COMM_WORLD);
    if (gCommRank == gMasterRank) {
        char commName[MPI_MAX_OBJECT_NAME]; int commNameLen;
        MPI_Comm_get_name(MPI_COMM_WORLD, commName, &commNameLen);
        auto currentTime = time(nullptr);

        std::cout <<
            "------------------------> Run starting <------------------------\n"
            " MTransportMC\n"
            "  A muonium transport simulation tool.\n"
            "\n"
            " This run is named <" << gName << ">.\n"
            " Running " << gCommSize << " processes in " << commName << ".\n"
            "\n"
            " Physical parameters and simulation configurations:\n"
            "  Target region:\n"
            "   " << gTargetFormula << "\n"
            "  Step length of pushing:\n"
            "   " << gStepOfPushing << " [um]\n"
            "  Periodic boundary:\n"
#ifdef PERIODIC_BOUNDARY_X
            "   |x|=" << gPeriodicBoundaryX << " [um]"
#endif
#ifdef PERIODIC_BOUNDARY_Y
            "   |y|=" << gPeriodicBoundaryY << " [um]"
#endif
#ifdef PERIODIC_BOUNDARY_Z
            "   |z|=" << gPeriodicBoundaryZ << " [um]"
#endif
            "\n"
            "  Muonium life:\n"
            "   " << gMuoniumLife << " [us]\n"
            "  Muonium Mass:\n"
            "   " << gMuoniumMass << " [MeV]\n"
            "  Muonium transportation mean free path:\n"
            "   " << gMeanFreePathFormula << " [um]\n"
            "  Temperature:\n"
            "   " << gTemperature << " [K]\n"
            "  Muonium source:\n"
            "   " << gSourceFormula << " [1/um^3]\n"
            "   in range (" << gSourceXMin << "," << gSourceXMax << ")x(" << gSourceYMin << "," << gSourceYMax << ")x(" << gSourceZMin << "," << gSourceZMax << ") [um^3]\n"
            "  Total number of muonium:\n"
            "   " << gMuoniumNum << "\n"
            "  Simulation start time:\n"
            "   " << gBeginTime << " [us]\n"
            "  Result output time step:\n"
            "   " << gOutputStep << " [us]\n"
            "  Simulation end time:\n"
            "   " << gEndTime << " [us]\n"
            "                                       " << ctime(&currentTime) <<
            "------------------------> Run starting <------------------------\n"
            "Master at " << processorName << " has initialized." << std::endl;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (gCommRank != gMasterRank) {
        std::cout << "Worker " << gCommRank << " at " << processorName << " has initialized." << std::endl;
    }
}

void RunManager::FinalReport() const {
    if (fStatus != kRunStopped) { return; }

    char processorName[MPI_MAX_PROCESSOR_NAME]; int processorNameLen;
    MPI_Get_processor_name(processorName, &processorNameLen);

    auto recvCPUTime = new clock_t[gCommSize];
    clock_t sendCPUTime;
    MASTER_DO(sendCPUTime = fMaster->GetUsedCPUTime());
    WORKER_DO(sendCPUTime = fWorker->GetUsedCPUTime());
    MPI_Gather(&sendCPUTime, 1, MPI_LONG, recvCPUTime, 1, MPI_LONG, gMasterRank, MPI_COMM_WORLD);

    auto currentTime = time(nullptr);

    if (gCommRank == gMasterRank) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clock_t totalCPUTime = 0;
        for (int i = 0; i < gCommSize; ++i) {
            totalCPUTime += recvCPUTime[i];
        }
        auto runBeginTime = fMaster->GetRunBeginTime();
        auto runEndTime = fMaster->GetRunEndTime();
        std::cout <<
            ctime(&currentTime) <<
            "Master at " << processorName << " is finalizing.\n"
            "-----------------------> Run completed. <-----------------------\n"
            " Begin time: " << ctime(&runBeginTime) <<
            "   End time: " << ctime(&runEndTime) <<
            "  Wall time: " << difftime(runEndTime, runBeginTime) << "s\n"
            "   CPU time: " << totalCPUTime / CLOCKS_PER_SEC << "s\n"
            "-----------------------> Run completed. <-----------------------" << std::endl;
    } else {
        std::cout <<
            ctime(&currentTime) <<
            "Worker " << gCommRank << " at " << processorName << " is finalizing." << std::endl;
    }

    delete[] recvCPUTime;
}

