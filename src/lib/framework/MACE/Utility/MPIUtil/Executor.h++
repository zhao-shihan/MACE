#pragma once

#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/Concept/MPIPredefined.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/stdx/boolean_testable.h++"
#include "MACE/Utility/CPUTimeStopwatch.h++"
#include "MACE/Utility/MPIUtil/DynamicScheduler.h++"
#include "MACE/Utility/MPIUtil/Scheduler.h++"
#include "MACE/Utility/WallTimeStopwatch.h++"

#include "mpi.h"

#include "fmt/chrono.h"
#include "fmt/format.h"

#include <cassert>
#include <chrono>
#include <cmath>
#include <concepts>
#include <cstdio>
#include <memory>
#include <optional>
#include <stdexcept>
#include <tuple>

namespace MACE::inline Utility::MPIUtil {

template<template<typename> typename>
struct ScheduleBy {};

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class Executor final {
public:
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    Executor(ScheduleBy<S> = {});
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    explicit Executor(Scheduler<T>::Task task, ScheduleBy<S> = {});
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    Executor(T first, T last, ScheduleBy<S> = {});
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    explicit Executor(T size, ScheduleBy<S> = {});

    template<template<typename> typename AScheduler>
        requires std::derived_from<AScheduler<T>, Scheduler<T>>
    auto SwitchScheduler() -> void;

    auto AssignTask(Scheduler<T>::Task task) -> void;
    auto AssignTask(T first, T last) -> void { AssignTask({first, last}); }
    auto AssignTask(T size) -> void { AssignTask({0, size}); }

    auto PrintProgressModulo(T mod) -> void { fPrintProgressModulo = mod; }
    auto ExecutionName(std::string name) -> void { fExecutionName = std::move(name); }
    auto TaskName(std::string name) -> void { fTaskName = std::move(name); }

    auto Task() const -> auto { return fScheduler->fTask; }
    auto NTask() const -> T { return fScheduler->NTask(); }
    auto Executing() const -> bool { return fExecuting; }

    auto Execute(std::invocable<T> auto&& Func) -> T;

    auto ExecutingTask() const -> T { return fScheduler->fExecutingTask; }
    auto NLocalExecutedTask() const -> T { return fScheduler->fNLocalExecutedTask; }
    auto NExecutedTask() const -> T { return fScheduler->NExecutedTask(); }

private:
    auto PreLoopReport() const -> void;
    auto PostTaskReport(T iEnded) const -> void;
    auto PostLoopReport() const -> void;

    static auto SToDHMS(double s) -> std::string;

private:
    using scsc = std::chrono::system_clock;

private:
    std::unique_ptr<Scheduler<T>> fScheduler;

    bool fExecuting;

    T fPrintProgressModulo;

    WallTimeStopwatch<double> fWallTimeStopwatch;
    CPUTimeStopwatch<double> fCPUTimeStopwatch;
    double fExecutionWallTime;
    double fExecutionCPUTime;

    scsc::time_point fExecutionBeginSystemTime;
    scsc::time_point fExecutionEndSystemTime;

    std::string fExecutionName;
    std::string fTaskName;
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/Executor.inl"
