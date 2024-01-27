#pragma once

#include "MACE/Compatibility/std23/constexpr_cmath.h++"
#include "MACE/Concept/MPIPredefined.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/Execution/DynamicScheduler.h++"
#include "MACE/Extension/MPIX/Execution/Scheduler.h++"
#include "MACE/Extension/stdx/boolean_testable.h++"
#include "MACE/Utility/CPUTimeStopwatch.h++"
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
#include <numeric>
#include <optional>
#include <stdexcept>
#include <tuple>
#include <utility>

namespace MACE::inline Extension::MPIX::inline Execution {

template<template<typename> typename>
struct ScheduleBy {};

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
class Executor final {
public:
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    Executor(ScheduleBy<S> = {});
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    explicit Executor(typename Scheduler<T>::Task task, ScheduleBy<S> = {});
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    Executor(T first, T last, ScheduleBy<S> = {});
    template<template<typename> typename S = DynamicScheduler>
        requires std::derived_from<S<T>, Scheduler<T>>
    explicit Executor(T size, ScheduleBy<S> = {});

    template<template<typename> typename AScheduler>
        requires std::derived_from<AScheduler<T>, Scheduler<T>>
    auto SwitchScheduler() -> void;

    auto AssignTask(typename Scheduler<T>::Task task) -> void;
    auto AssignTask(T first, T last) -> void { AssignTask({first, last}); }
    auto AssignTask(T size) -> void { AssignTask({0, size}); }

    auto PrintProgress(bool a) -> void { fPrintProgress = a; }
    auto PrintProgressModulo(long long mod) -> void { fPrintProgressModulo = mod; }
    auto ExecutionName(std::string name) -> void { fExecutionName = std::move(name); }
    auto TaskName(std::string name) -> void { fTaskName = std::move(name); }

    auto Task() const -> auto { return fScheduler->fTask; }
    auto NTask() const -> T { return fScheduler->NTask(); }
    auto Executing() const -> bool { return fExecuting; }

    auto Execute(std::invocable<T> auto&& Func) -> T;

    auto ExecutingTask() const -> T { return fScheduler->fExecutingTask; }
    auto NLocalExecutedTask() const -> T { return fScheduler->fNLocalExecutedTask; }
    auto NExecutedTask() const -> T { return fScheduler->NExecutedTask(); }

    auto PrintExecutionSummary() const -> void;

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

    bool fPrintProgress;
    long long fPrintProgressModulo;
    mutable T fAutoPrintProgressModulo;

    std::string fExecutionName;
    std::string fTaskName;

    scsc::time_point fExecutionBeginSystemTime;
    WallTimeStopwatch<double> fWallTimeStopwatch;
    CPUTimeStopwatch<double> fCPUTimeStopwatch;
    std::array<double, 2> fExecutionWallTimeAndCPUTime;
    double& fExecutionWallTime;
    double& fExecutionCPUTime;

    std::vector<std::array<double, 2>> fExecutionWallTimeAndCPUTimeOfAllProcessKeptByMaster;
    std::vector<T> fNLocalExecutedTaskOfAllProcessKeptByMaster;
};

} // namespace MACE::inline Extension::MPIX::inline Execution

#include "MACE/Extension/MPIX/Execution/Executor.inl"
