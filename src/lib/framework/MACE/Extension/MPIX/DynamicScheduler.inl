namespace MACE::inline Extension::MPIX {

template<std::integral T>
DynamicScheduler<T>::DynamicScheduler() :
    Scheduler<T>{},
    fComm{},
    fBatchSize{},
    fContext{} {
    if (const auto mpiThreadSupport{Env::MPIEnv::Instance().MPIThreadSupport()};
        mpiThreadSupport < MPI_THREAD_MULTIPLE) {
        switch (mpiThreadSupport) {
        case MPI_THREAD_SINGLE:
            throw std::runtime_error{"the MPI library provides MPI_THREAD_SINGLE, "
                                     "but dynamic scheduler requires MPI_THREAD_MULTIPLE"};
        case MPI_THREAD_FUNNELED:
            throw std::runtime_error{"the MPI library provides MPI_THREAD_FUNNELED, "
                                     "but dynamic scheduler requires MPI_THREAD_MULTIPLE"};
        case MPI_THREAD_SERIALIZED:
            throw std::runtime_error{"the MPI library provides MPI_THREAD_SERIALIZED, "
                                     "but dynamic scheduler requires MPI_THREAD_MULTIPLE"};
        }
    }
    if (fComm.Rank() == 0) {
        fContext.template emplace<Master>(this);
    } else {
        fContext.template emplace<Worker>(this);
    }
}

template<std::integral T>
DynamicScheduler<T>::Comm::Comm() :
    fComm{
        [] {
            MPI_Comm comm;
            MPI_Comm_dup(MPI_COMM_WORLD, // comm
                         &comm);         // newcomm
            return comm;
        }()},
    fRank{
        [this] {
            int rank;
            MPI_Comm_rank(fComm,  // comm
                          &rank); // rank
            return rank;
        }()},
    fSize{
        [this] {
            int size;
            MPI_Comm_size(fComm,  // comm
                          &size); // size
            return size;
        }()} {}

template<std::integral T>
DynamicScheduler<T>::Comm::~Comm() {
    auto comm{fComm};
    MPI_Comm_free(&comm);
}

template<std::integral T>
auto DynamicScheduler<T>::PreLoopAction() -> void {
    fBatchSize = static_cast<T>(fgBalanceFactor * static_cast<double>(this->NTask()) / fComm.Size()) + 1;
    std::visit([](auto&& c) { c.PreLoopAction(); }, fContext);
}

template<std::integral T>
auto DynamicScheduler<T>::PreTaskAction() -> void {
    std::visit([](auto&& c) { c.PreTaskAction(); }, fContext);
}

template<std::integral T>
auto DynamicScheduler<T>::PostTaskAction() -> void {
    std::visit([](auto&& c) { c.PostTaskAction(); }, fContext);
}

template<std::integral T>
auto DynamicScheduler<T>::PostLoopAction() -> void {
    std::visit([](auto&& c) { c.PostLoopAction(); }, fContext);
}

template<std::integral T>
DynamicScheduler<T>::Master::Supervisor::Supervisor(DynamicScheduler<T>* ds) :
    fDS{ds},
    fMainTaskID{},
    fTaskIDSend{},
    fRecv{},
    fSend{} {
    fTaskIDSend.reserve(fDS->fComm.Size() - 1);
    fRecv.reserve(fDS->fComm.Size() - 1);
    fSend.reserve(fDS->fComm.Size() - 1);
    for (int src{1}; src < fDS->fComm.Size(); ++src) {
        MPI_Recv_init(nullptr,                // buf
                      0,                      // count
                      MPI_BYTE,               // datatype
                      src,                    // source
                      0,                      // tag
                      fDS->fComm,             // comm
                      &fRecv.emplace_back()); // request
    }
    for (int dest{1}; dest < fDS->fComm.Size(); ++dest) {
        MPI_Send_init(&fTaskIDSend.emplace_back(), // buf
                      1,                           // count
                      DataType<T>(),               // datatype
                      dest,                        // dest
                      1,                           // tag
                      fDS->fComm,                  // comm
                      &fSend.emplace_back());      // request
    }
}

template<std::integral T>
DynamicScheduler<T>::Master::Supervisor::~Supervisor() {
    for (auto&& s : fSend) { MPI_Request_free(&s); }
    for (auto&& r : fRecv) { MPI_Request_free(&r); }
}

template<std::integral T>
auto DynamicScheduler<T>::Master::Supervisor::Supervise() -> void {
    MPI_Startall(fRecv.size(),  // count
                 fRecv.data()); // array_of_requests
    // inform workers that receive have been posted
    for (int dest{1}; dest < fDS->fComm.Size(); ++dest) {
        MPI_Request send;
        MPI_Isend(nullptr,    // buf
                  0,          // count
                  MPI_BYTE,   // datatype
                  dest,       // dest
                  2,          // tag
                  fDS->fComm, // comm
                  &send);     // request
        MPI_Request_free(&send);
    }
    bool scheduling{true};
    do {
        int cgCount;
        std::vector<int> cgRank(fDS->fComm.Size() - 1);
        MPI_Waitsome(fRecv.size(),         // incount
                     fRecv.data(),         // array_of_requests
                     &cgCount,             // outcount
                     cgRank.data(),        // array_of_indices
                     MPI_STATUSES_IGNORE); // array_of_statuses
        for (int i{}; i < cgCount; ++i) {
            const auto c{cgRank[i]};
            fTaskIDSend[c] = FetchAddTaskID();
            if (fTaskIDSend[c] == fDS->fTask.last) {
                scheduling = false;
                break;
            }
            MPI_Start(&fRecv[c]);
            MPI_Wait(&fSend[c],          // request
                     MPI_STATUS_IGNORE); // status
            MPI_Start(&fSend[c]);
        }
    } while (scheduling);
    MPI_Waitall(fSend.size(),         // count
                fSend.data(),         // array_of_requests
                MPI_STATUSES_IGNORE); // array_of_statuses
    for (auto&& i : fTaskIDSend) { i = fDS->fTask.last; }
    MPI_Waitall(fRecv.size(),         // count
                fRecv.data(),         // array_of_requests
                MPI_STATUSES_IGNORE); // array_of_statuses
    MPI_Startall(fSend.size(),        // count
                 fSend.data());       // array_of_requests
    MPI_Waitall(fSend.size(),         // count
                fSend.data(),         // array_of_requests
                MPI_STATUSES_IGNORE); // array_of_statuses
}

template<std::integral T>
auto DynamicScheduler<T>::Master::Supervisor::FetchAddTaskID() -> T {
    return std::min(fMainTaskID.fetch_add(fDS->fBatchSize, std::memory_order::relaxed),
                    fDS->fTask.last);
}

template<std::integral T>
DynamicScheduler<T>::Master::Master(DynamicScheduler<T>* ds) :
    fDS{ds},
    fSupervisor{ds},
    fSupervisorThread{},
    fBatchCounter{} {}

template<std::integral T>
DynamicScheduler<T>::Master::~Master() {
    if (fSupervisorThread.joinable()) { fSupervisorThread.join(); } // wait for supervision to end if needed
}

template<std::integral T>
auto DynamicScheduler<T>::Master::PreLoopAction() -> void {
    fSupervisor.ResetTaskID();
    if (fDS->fComm.Size() >= 2) {
        if (fSupervisorThread.joinable()) { fSupervisorThread.join(); } // wait for last supervision to end if needed
        fSupervisorThread = std::jthread{[this] { fSupervisor.Supervise(); }};
    }
    fDS->fExecutingTask = fDS->fTask.first;
    fBatchCounter = 0;
}

template<std::integral T>
auto DynamicScheduler<T>::Master::PostTaskAction() -> void {
    if (++fBatchCounter == fDS->fBatchSize) {
        fBatchCounter = 0;
        fDS->fExecutingTask = fSupervisor.FetchAddTaskID();
    } else {
        ++fDS->fExecutingTask;
    }
}

template<std::integral T>
DynamicScheduler<T>::Worker::Worker(DynamicScheduler<T>* ds) :
    fDS{ds},
    fTaskIDRecv{},
    fRequest{},
    fBatchCounter{} {
    auto& [send, recv]{fRequest};
    MPI_Send_init(nullptr,       // buf
                  0,             // count
                  MPI_BYTE,      // datatype
                  0,             // dest
                  0,             // tag
                  fDS->fComm,    // comm
                  &send);        // request
    MPI_Recv_init(&fTaskIDRecv,  // buf
                  1,             // count
                  DataType<T>(), // datatype
                  0,             // source
                  1,             // tag
                  fDS->fComm,    // comm
                  &recv);        // request
}

template<std::integral T>
DynamicScheduler<T>::Worker::~Worker() {
    auto& [send, recv]{fRequest};
    MPI_Request_free(&recv);
    MPI_Request_free(&send);
}

template<std::integral T>
auto DynamicScheduler<T>::Worker::PreLoopAction() -> void {
    fDS->fExecutingTask = fDS->fTask.first + fDS->fComm.Rank() * fDS->fBatchSize;
    fBatchCounter = 0;
    // wait for scheduler to post receive
    MPI_Recv(nullptr,            // buf
             0,                  // count
             MPI_BYTE,           // datatype
             0,                  // source
             2,                  // tag
             fDS->fComm,         // comm
             MPI_STATUS_IGNORE); // status
}

template<std::integral T>
auto DynamicScheduler<T>::Worker::PreTaskAction() -> void {
    if (fBatchCounter == 0) {
        auto& [send, recv]{fRequest};
        MPI_Start(&recv);
        MPI_Start(&send);
    }
}

template<std::integral T>
auto DynamicScheduler<T>::Worker::PostTaskAction() -> void {
    if (++fBatchCounter == fDS->fBatchSize) {
        fBatchCounter = 0;
        MPI_Waitall(fRequest.size(),      // count
                    fRequest.data(),      // array_of_requests
                    MPI_STATUSES_IGNORE); // array_of_statuses
        fDS->fExecutingTask = fTaskIDRecv;
    } else {
        ++fDS->fExecutingTask;
    }
}

} // namespace MACE::inline Extension::MPIX
