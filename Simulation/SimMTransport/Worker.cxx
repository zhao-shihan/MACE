#include "Worker.hxx"

#include "SimMTransport/Analysis.hxx"

using namespace MACE::SimMTransport;

Worker::Worker() :
    fTrack(new Track()),
    fBeginCPUTime(0),
    fEndCPUTime(0) {}

Worker::~Worker() {
    delete fTrack;
}

void Worker::Initialize() {
    Analysis::Instance()->Open();
    fBeginCPUTime = clock();
}

void Worker::Run() {
    size_t thisJob, nextJob;
    MPI_Request request;
    MPI_Recv_init(&nextJob, 1, MPI_UNSIGNED_LONG, Global::Instance()->MasterRank(), 0, MPI_COMM_WORLD, &request);
    MPI_Start(&request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    thisJob = nextJob;
    while (thisJob > 0) {
        MPI_Start(&request);
        do {
            fTrack->Initialize();
            do {
                fTrack->Stepping();
            } while (fTrack->GetTrackStatus() == kTrackAlive);
            --thisJob;
        } while (thisJob > 0);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        thisJob = nextJob;
    }
    MPI_Request_free(&request);
}

void Worker::Finalize() {
    fEndCPUTime = clock();
    Analysis::Instance()->WriteAndClose();
    delete Analysis::Instance();
}
