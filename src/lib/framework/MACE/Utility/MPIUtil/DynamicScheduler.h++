#pragma once

#include "MACE/Compatibility/std2b/unreachable.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/DataType.h++"
#include "MACE/Utility/MPIUtil/Scheduler.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "mpi.h"

#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <variant>
#include <vector>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
class DynamicScheduler final : public Scheduler<T> {
public:
    DynamicScheduler();

private:
    auto PreLoopAction() -> void override;
    auto PreTaskAction() -> void override;
    auto PostTaskAction() -> void override;
    auto PostLoopAction() -> void override;

private:
    class Comm final {
    public:
        Comm();
        ~Comm();

        operator MPI_Comm() const { return fComm; }
        auto Rank() const -> int { return fRank; }
        auto Size() const -> int { return fSize; }

    private:
        const MPI_Comm fComm;
        const int fRank;
        const int fSize;
    };

    struct Dummy final : std::monostate {
        auto PreLoopAction() -> void { std2b::unreachable(); }
        auto PreTaskAction() -> void { std2b::unreachable(); }
        auto PostTaskAction() -> void { std2b::unreachable(); }
        auto PostLoopAction() -> void { std2b::unreachable(); }
    };

    class Master final : public NonMoveableBase {
    public:
        Master(DynamicScheduler<T>* ds);
        ~Master();

        auto PreLoopAction() -> void;
        auto PreTaskAction() -> void {}
        auto PostTaskAction() -> void;
        auto PostLoopAction() -> void {}

    private:
        class Supervisor final : public NonMoveableBase {
        public:
            Supervisor(DynamicScheduler<T>* ds);
            ~Supervisor();

            auto ResetTaskID() -> void { fMainTaskID = fDS->fTask.first + fDS->fComm.Size() * fDS->fBatchSize; }
            auto FetchAddTaskID() -> T;

            auto Supervise() -> void;

        private:
            DynamicScheduler<T>* const fDS;

            std::atomic<T> fMainTaskID;

            std::vector<T> fTaskIDSend;
            std::vector<MPI_Request> fRecv;
            std::vector<MPI_Request> fSend;
        };

    private:
        DynamicScheduler<T>* const fDS;

        Supervisor fSupervisor;
        std::jthread fSupervisorThread;

        T fBatchCounter;
    };
    friend class Master;

    class Worker final : public NonMoveableBase {
    public:
        Worker(DynamicScheduler<T>* ds);
        ~Worker();

        auto PreLoopAction() -> void;
        auto PreTaskAction() -> void;
        auto PostTaskAction() -> void;
        auto PostLoopAction() -> void {}

    private:
        DynamicScheduler<T>* const fDS;

        T fTaskIDRecv;
        std::array<MPI_Request, 2> fRequest;
        T fBatchCounter;
    };
    friend class Worker;

private:
    const Comm fComm;
    T fBatchSize;
    std::variant<Dummy, Master, Worker> fContext;

    static constexpr auto fgBalanceFactor{0.01};
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/DynamicScheduler.inl"
