#pragma once

#include "MACE/Concept/MPIPredefined.h++"

#include <concepts>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class Scheduler;

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class SchedulerKernel {
    friend class Scheduler<T>;

protected:
    struct Task {
        T first;
        T last;
    };

public:
    SchedulerKernel() = default;
    SchedulerKernel(Task task);
    virtual ~SchedulerKernel() = default;

private:
    virtual auto PreRunAction() -> void = 0;
    virtual auto PreTaskAction() -> void = 0;
    virtual auto PostTaskAction() -> void = 0;
    virtual auto PostRunAction() -> void = 0;

protected:
    Task fTask;
    T fProcessingTask;
    T fNLocalProcessedTask;
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/SchedulerKernel.inl"
