#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/Execution/Scheduler.h++"

#include <concepts>
#include <utility>

namespace MACE::inline Extension::MPIX::inline Execution {

template<std::integral T>
class StaticScheduler : public Scheduler<T> {
    virtual auto PreLoopAction() -> void override;
    virtual auto PreTaskAction() -> void override {}
    virtual auto PostTaskAction() -> void override;
    virtual auto PostLoopAction() -> void override {}

    virtual auto NExecutedTask() const -> std::pair<bool, T> override;
};

} // namespace MACE::inline Extension::MPIX::inline Execution

#include "MACE/Extension/MPIX/Execution/StaticScheduler.inl"
