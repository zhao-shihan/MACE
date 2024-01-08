#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/SchedulerKernel.h++"

#include <concepts>
#include <optional>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
class StaticSchedulerKernel final : public SchedulerKernel<T> {
public:
    using SchedulerKernel<T>::SchedulerKernel;

private:
    auto PreRunAction() -> void override;
    auto PreTaskAction() -> void override {}
    auto PostTaskAction() -> void override;
    auto PostRunAction() -> void override {}
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/StaticSchedulerKernel.inl"
