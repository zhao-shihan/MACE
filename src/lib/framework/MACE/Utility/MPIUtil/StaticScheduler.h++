#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/Scheduler.h++"

#include <concepts>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
class StaticScheduler final : public Scheduler<T> {
    auto PreLoopAction() -> void override;
    auto PreTaskAction() -> void override {}
    auto PostTaskAction() -> void override;
    auto PostLoopAction() -> void override {}
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/StaticScheduler.inl"
