#include <ctime>

#include "Master.hxx"

using namespace MACE::SimMTransport;

Master::Master() :
    fBeginCPUTime(0),
    fEndCPUTime(0),
    fRunBeginTime(0),
    fRunEndTime(0) {}

void Master::Initialize() {
    time(&fRunBeginTime);
    fBeginCPUTime = clock();
}

void Master::Run() {
    auto workersJob = new size_t[Global::Instance()->WorkerNum()];
    auto requests = new MPI_Request[Global::Instance()->WorkerNum()];
    size_t jobSend = 0;
    int finished = 0;
    for (int dest = 0; dest < Global::Instance()->WorkerNum(); ++dest) {
        MPI_Ssend_init(workersJob + dest, 1, MPI_UNSIGNED_LONG, dest, 0, MPI_COMM_WORLD, requests + dest);
        workersJob[dest] = std::min(Global::Instance()->WorkerJobSize(), Global::Instance()->MuoniumNum() - jobSend);
        MPI_Start(requests + dest);
        jobSend += workersJob[dest];
        finished += (workersJob[dest] == 0);
    }
    while (jobSend < Global::Instance()->MuoniumNum()) {
        int dest;
        MPI_Waitany(Global::Instance()->WorkerNum(), requests, &dest, MPI_STATUS_IGNORE);
        workersJob[dest] = std::min(Global::Instance()->WorkerJobSize(), Global::Instance()->MuoniumNum() - jobSend);
        MPI_Start(requests + dest);
        jobSend += workersJob[dest];
        ProgressReport(jobSend);
    }
    while (finished < Global::Instance()->WorkerNum()) {
        int dest;
        MPI_Waitany(Global::Instance()->WorkerNum(), requests, &dest, MPI_STATUS_IGNORE);
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
    size_t estJobDone = jobSend - Global::Instance()->WorkerJobSize() * Global::Instance()->WorkerNum();
    time_t currentTime = time(nullptr);
    time_t eta = double(Global::Instance()->MuoniumNum() - estJobDone) * double(currentTime - fRunBeginTime) / double(estJobDone);
    time_t etaHr = eta / 3600;
    time_t etaMin = (eta - etaHr * 3600) / 60;
    time_t etaSec = eta - (etaMin * 60 + etaHr * 3600);
    std::cout
        << ctime(&currentTime)
        << jobSend << '/' << Global::Instance()->MuoniumNum() << " have been assigned ("
        << 100.f * float(jobSend) / Global::Instance()->MuoniumNum() << "%). "
        << "ETA: " << etaHr << "h " << etaMin << "m " << etaSec << 's'
        << std::endl;
}

