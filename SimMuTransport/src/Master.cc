#include <ctime>

#include "Master.hh"

using namespace MACE::SimMuTransport;

Master::Master() :
    fBeginCPUTime(0),
    fEndCPUTime(0),
    fRunBeginTime(0),
    fRunEndTime(0) {}

Master::~Master() {}

void Master::Initialize() {
    time(&fRunBeginTime);
    fBeginCPUTime = clock();
}

void Master::Run() {
    auto workersJob = new size_t[gWorkerNum];
    auto requests = new MPI_Request[gWorkerNum];
    size_t jobSend = 0;
    int finished = 0;
    for (int dest = 0; dest < gWorkerNum; ++dest) {
        MPI_Ssend_init(workersJob + dest, 1, MPI_UNSIGNED_LONG, dest, 0, MPI_COMM_WORLD, requests + dest);
        workersJob[dest] = std::min(gWorkerJobSize, gMuoniumNum - jobSend);
        MPI_Start(requests + dest);
        jobSend += workersJob[dest];
        finished += (workersJob[dest] == 0);
    }
    while (jobSend < gMuoniumNum) {
        int dest;
        MPI_Waitany(gWorkerNum, requests, &dest, MPI_STATUS_IGNORE);
        workersJob[dest] = std::min(gWorkerJobSize, gMuoniumNum - jobSend);
        MPI_Start(requests + dest);
        jobSend += workersJob[dest];
        ProgressReport(jobSend);
    }
    while (finished < gWorkerNum) {
        int dest;
        MPI_Waitany(gWorkerNum, requests, &dest, MPI_STATUS_IGNORE);
        if (workersJob[dest] > 0) {
            workersJob[dest] = 0;
            MPI_Start(requests + dest);
            ++finished;
        }
        MPI_Request_free(requests + dest);
    }
    delete[] requests;
    delete[] workersJob;
}

void Master::Finalize() {
    fEndCPUTime = clock();
    time(&fRunEndTime);
}

void Master::ProgressReport(size_t jobSend) const {
    size_t estJobDone = jobSend - gWorkerJobSize * gWorkerNum;
    time_t currentTime = time(nullptr);
    time_t eta = double(gMuoniumNum - estJobDone) * double(currentTime - fRunBeginTime) / double(estJobDone);
    time_t etaHr = eta / 3600;
    time_t etaMin = (eta - etaHr * 3600) / 60;
    time_t etaSec = eta - (etaMin * 60 + etaHr * 3600);
    std::cout
        << ctime(&currentTime)
        << jobSend << '/' << gMuoniumNum << " have been assigned ("
        << 100.f * float(jobSend) / gMuoniumNum << "%). "
        << "ETA: " << etaHr << "h " << etaMin << "m " << etaSec << 's'
        << std::endl;
}

