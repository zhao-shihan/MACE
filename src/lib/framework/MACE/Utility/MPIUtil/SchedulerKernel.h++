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

public:
    SchedulerKernel() = default;
    SchedulerKernel(T first, T last);
    virtual ~SchedulerKernel() = default;

private:
    virtual auto PreRunAction() -> void = 0;
    virtual auto PreTaskAction() -> void = 0;
    virtual auto PostTaskAction() -> void = 0;
    virtual auto PostRunAction() -> void = 0;

protected:
    struct {
        T first;
        T last;
    } fTask;
    T fProcessingTask;
    T fNLocalProcessedTask;
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/SchedulerKernel.inl"
