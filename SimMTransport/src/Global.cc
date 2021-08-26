#include "Global.hh"
#include "Analysis.hh"
#include "RunManager.hh"

using namespace MACE::SimMTransport;

const MPIGlobal* gMPIGlobal = nullptr;

MPIGlobal::MPIGlobal(int commRank, int commSize) :
    fCommRank(commRank), fCommSize(commSize),
    fMasterRank(commSize - 1), fWorkerNum(commSize - 1) {}

MPIGlobal::~MPIGlobal() {}

void MPIGlobal::Initialize(int* argc, char*** argv) {
    if (gMPIGlobal != nullptr) { return; }

    MPI_Init(argc, argv);

    int commRank; MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
    int commSize; MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    if (commSize < 2) {
        delete RunManager::Instance();
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    
    gMPIGlobal = new MPIGlobal(commRank, commSize);
}

void MPIGlobal::Finalize() {
    if (gMPIGlobal == nullptr) { return; }

    delete gMPIGlobal;
    gMPIGlobal = nullptr;

    MPI_Finalize();
}

