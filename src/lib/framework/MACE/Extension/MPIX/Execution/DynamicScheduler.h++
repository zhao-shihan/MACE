#pragma once

#include "MACE/Compatibility/std23/unreachable.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/DataType.h++"
#include "MACE/Extension/MPIX/Execution/Scheduler.h++"
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

namespace MACE::inline Extension::MPIX::inline Execution {

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
        auto PreLoopAction() -> void { std23::unreachable(); }
        auto PreTaskAction() -> void { std23::unreachable(); }
        auto PostTaskAction() -> void { std23::unreachable(); }
        auto PostLoopAction() -> void { std23::unreachable(); }
    };

    class Master final : public NonMoveableBase {
    public:
        Master(DynamicScheduler<T>* ds);

        auto PreLoopAction() -> void;
        auto PreTaskAction() -> void {}
        auto PostTaskAction() -> void;
        auto PostLoopAction() -> void {}

    private:
        class Supervisor final : public NonMoveableBase {
        public:
            Supervisor(DynamicScheduler<T>* ds);
            ~Supervisor();

            auto FetchAddTaskID() -> T;

            auto Start() -> void;

        private:
            DynamicScheduler<T>* const fDS;
            std::atomic<T> fMainTaskID;
            std::vector<MPI_Request> fRecv;
            std::vector<T> fTaskIDSend;
            std::vector<MPI_Request> fSend;
            std::jthread fSupervisorThread;
        };

    private:
        DynamicScheduler<T>* const fDS;
        Supervisor fSupervisor;
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
        auto PostLoopAction() -> void;

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

} // namespace MACE::inline Extension::MPIX::inline Execution

#include "MACE/Extension/MPIX/Execution/DynamicScheduler.inl"
