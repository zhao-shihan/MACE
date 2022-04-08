#include "RunManager.hxx"
#include "MACE/Simulation/SimMTransport/Analysis.hxx"

#include <thread>

using MACE::Simulation::SimMTransport::RunManager;

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

#define MASTER_DO(statement) \
    if (Global::Instance()->CommRank() == Global::Instance()->MasterRank()) statement
#define WORKER_DO(statement) \
    else statement

void RunManager::Initialize(int& argc, char**& argv) {
    if (fStatus == kRunRunning or fStatus == kRunStopped) { return; }

    Global::Initialize(argc, argv);

    MASTER_DO(fMaster = new Master());
    WORKER_DO(fWorker = new Worker());

    InitialReport();
    // ToDo: check Global::Instance()->MeanFreePath() grad.

    MASTER_DO(fMaster->Initialize());
    WORKER_DO(fWorker->Initialize());

    fStatus = kRunInitialized;
}

void RunManager::Run() {
    if (fStatus == kRunUndefined or fStatus == kRunFinalized) { return; }
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

    Global::Finalize();

    fStatus = kRunFinalized;
}

void RunManager::InitialReport() const {
    if (fStatus == kRunRunning or fStatus == kRunStopped) { return; }

    char processorName[MPI_MAX_PROCESSOR_NAME];
    int processorNameLen;
    MPI_Get_processor_name(processorName, &processorNameLen);

    auto global = Global::Instance();

    MPI_Barrier(MPI_COMM_WORLD);
    if (global->CommRank() == global->MasterRank()) {
        char commName[MPI_MAX_OBJECT_NAME];
        int commNameLen;
        MPI_Comm_get_name(MPI_COMM_WORLD, commName, &commNameLen);
        double xMin, xMax, yMin, yMax, zMin, zMax;
        global->Source()->GetRange(xMin, xMax, yMin, yMax, zMin, zMax);
        auto currentTime = time(nullptr);

        std::cout
            << "------------------------> Run starting <------------------------\n"
            << " MTransportMC\n"
            << "  A muonium transport simulation tool.\n"
            << "\n"
            << " This run is named <" << global->Name() << ">.\n"
            << " Running " << global->CommSize() << " processes in " << commName << ".\n"
            << "\n"
            << " Physical parameters and simulation configurations:\n"
            << "  Target region:\n"
            << "   " << global->Target()->GetExpFormula() << "\n"
            << "  Step length of pushing:\n"
            << "   " << global->StepOfPushing() << " [um]\n"
            << "  Periodic boundary:\n"
            << "   |x|=" << global->PeriodicBoundaryX() << " [um]   |y|=" << global->PeriodicBoundaryY() << " [um]   |z|=" << global->PeriodicBoundaryZ() << " [um]\n"
            << "  Muonium life:\n"
            << "   " << global->MuoniumLife() << " [us]\n"
            << "  Muonium Mass:\n"
            << "   " << global->MuoniumMass() << " [MeV]\n"
            << "  Muonium transportation mean free path:\n"
            << "   " << global->MeanFreePath()->GetExpFormula() << " [um]\n"
            << "  Temperature:\n"
            << "   " << global->Temperature() << " [K]\n"
            << "  Muonium source:\n"
            << "   " << global->Source()->GetExpFormula() << " [1/um^3]\n"
            << "   in range (" << xMin << "," << xMax << ")x(" << yMin << "," << yMax << ")x(" << zMin << "," << zMax << ") [um^3]\n"
            << "  Total number of muonium:\n"
            << "   " << global->MuoniumNum() << "\n"
            << "  Simulation start time:\n"
            << "   " << global->BeginTime() << " [us]\n"
            << "  Result output time step:\n"
            << "   " << global->OutputStep() << " [us]\n"
            << "  Simulation end time:\n"
            << "   " << global->EndTime() << " [us]\n"
            << "                                       " << ctime(&currentTime)
            << "------------------------> Run starting <------------------------\n"
            << "Master at " << processorName << " has initialized."
            << std::endl;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (global->CommRank() != global->MasterRank()) {
        std::cout << "Worker " << global->CommRank() << " at " << processorName << " has initialized." << std::endl;
    }
}

void RunManager::FinalReport() const {
    if (fStatus != kRunStopped) { return; }

    char processorName[MPI_MAX_PROCESSOR_NAME];
    int processorNameLen;
    MPI_Get_processor_name(processorName, &processorNameLen);

    auto global = Global::Instance();

    auto recvCPUTime = new clock_t[global->CommSize()];
    clock_t sendCPUTime;
    MASTER_DO(sendCPUTime = fMaster->GetUsedCPUTime());
    WORKER_DO(sendCPUTime = fWorker->GetUsedCPUTime());
    MPI_Gather(&sendCPUTime, 1, MPI_LONG, recvCPUTime, 1, MPI_LONG, global->MasterRank(), MPI_COMM_WORLD);

    auto currentTime = time(nullptr);

    if (global->CommRank() == global->MasterRank()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clock_t totalCPUTime = 0;
        for (int i = 0; i < global->CommSize(); ++i) {
            totalCPUTime += recvCPUTime[i];
        }
        auto runBeginTime = fMaster->GetRunBeginTime();
        auto runEndTime = fMaster->GetRunEndTime();
        std::cout << ctime(&currentTime) << "Master at " << processorName << " is finalizing.\n"
                                                                             "-----------------------> Run completed. <-----------------------\n"
                                                                             " Begin time: "
                  << ctime(&runBeginTime) << "   End time: " << ctime(&runEndTime) << "  Wall time: " << difftime(runEndTime, runBeginTime) << "s\n"
                                                                                                                                               "   CPU time: "
                  << totalCPUTime / CLOCKS_PER_SEC << "s\n"
                                                      "-----------------------> Run completed. <-----------------------"
                  << std::endl;
    } else {
        std::cout << ctime(&currentTime) << "Worker " << global->CommRank() << " at " << processorName << " is finalizing." << std::endl;
    }

    delete[] recvCPUTime;
}
