#pragma once

#include "MACE/Concept/MPIPredefined.h++"

#include <concepts>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class Executor;

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class Scheduler {
    friend class Executor<T>;

protected:
    struct Task {
        T first;
        T last;
    };

public:
    virtual ~Scheduler() = default;

protected:
    auto NTask() const -> T { return fTask.last - fTask.first; }
    auto NExecutedTask() const -> T { return fExecutingTask - fTask.first; }

private:
    auto Reset() -> void;

    virtual auto PreLoopAction() -> void = 0;
    virtual auto PreTaskAction() -> void = 0;
    virtual auto PostTaskAction() -> void = 0;
    virtual auto PostLoopAction() -> void = 0;

protected:
    Task fTask;
    T fExecutingTask;
    T fNLocalExecutedTask;
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/Scheduler.inl"
