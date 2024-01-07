#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/TaskScheduler.h++"

#include <concepts>
#include <optional>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
class StaticTaskScheduler final : public TaskScheduler<T> {
public:
    StaticTaskScheduler();
    explicit StaticTaskScheduler(T size);
    StaticTaskScheduler(T first, T last);

private:
    auto PreRunAction() -> void override;
    auto PreTaskAction() -> void override {}
    auto PostTaskAction() -> void override;
    auto PostRunAction() -> void override {}
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/StaticTaskScheduler.inl"
