#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/Scheduler.h++"

#include <concepts>

namespace MACE::inline Extension::MPIX {

template<std::integral T>
class StaticScheduler final : public Scheduler<T> {
    auto PreLoopAction() -> void override;
    auto PreTaskAction() -> void override {}
    auto PostTaskAction() -> void override;
    auto PostLoopAction() -> void override {}
};

} // namespace MACE::inline Extension::MPIX

#include "MACE/Extension/MPIX/StaticScheduler.inl"
