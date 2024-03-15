#pragma once

#include "MACE/Concept/MPIPredefined.h++"

#include <concepts>
#include <utility>

namespace MACE::inline Extension::MPIX::inline Execution {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
class Executor;

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
class Scheduler {
    friend class Executor<T>;

public:
    virtual ~Scheduler() = default;

protected:
    auto NTask() const -> T { return fTask.last - fTask.first; }

private:
    auto Reset() -> void;

    virtual auto PreLoopAction() -> void = 0;
    virtual auto PreTaskAction() -> void = 0;
    virtual auto PostTaskAction() -> void = 0;
    virtual auto PostLoopAction() -> void = 0;

    virtual auto NExecutedTask() const -> std::pair<bool, T> = 0;

protected:
    struct Task {
        T first;
        T last;
    };

protected:
    Task fTask;
    T fExecutingTask;
    T fNLocalExecutedTask;
};

} // namespace MACE::inline Extension::MPIX::inline Execution

#include "MACE/Extension/MPIX/Execution/Scheduler.inl"
