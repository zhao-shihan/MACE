#pragma once

#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/Concept/MPIPredefined.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/CPUTimeStopwatch.h++"
#include "MACE/Utility/MPIUtil/SchedulerKernel.h++"
#include "MACE/Utility/MPIUtil/StaticSchedulerKernel.h++"
#include "MACE/Utility/WallTimeStopwatch.h++"

#include "mpi.h"

#include "fmt/chrono.h"
#include "fmt/format.h"

#include <chrono>
#include <cmath>
#include <concepts>
#include <cstdio>
#include <memory>
#include <optional>
#include <stdexcept>
#include <tuple>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class Scheduler final {
public:
    Scheduler();
    explicit Scheduler(SchedulerKernel<T>::Task task);
    Scheduler(T first, T last);
    explicit Scheduler(T size);

    template<template<typename> typename AKernel>
        requires std::derived_from<AKernel<T>, SchedulerKernel<T>>
    auto SwitchKernel() -> void;

    auto AssignTask(SchedulerKernel<T>::Task task) -> void;
    auto AssignTask(T first, T last) -> void { AssignTask({first, last}); }
    auto AssignTask(T size) -> void { AssignTask({0, size}); }
    auto Reset() -> void;

    auto PrintProgressModulo(T mod) -> void { fPrintProgressModulo = mod; }
    auto RunName(std::string name) -> void { fRunName = std::move(name); }
    auto TaskName(std::string name) -> void { fTaskName = std::move(name); }

    auto Processing() const -> bool { return fProcessing; }
    auto Task() const -> auto { return fKernel->fTask; }
    auto NTask() const -> T { return fKernel->fTask.last - fKernel->fTask.first; }
    auto Deficient() const -> bool { return Env::MPIEnv::Instance().CommWorldSize() > NTask(); }

    auto Next() -> std::optional<T>;

    auto ProcessingTask() const -> T { return fKernel->fProcessingTask; }
    auto NLocalProcessedTask() const -> T { return fKernel->fNLocalProcessedTask; }
    auto NProcessedTask() const -> T { return fKernel->fProcessingTask - fKernel->fTask.first; }

private:
    auto PreRunReport() const -> void;
    auto PostTaskReport(T iEnded) const -> void;
    auto PostRunReport() const -> void;

    static auto SToDHMS(double s) -> std::string;

private:
    using scsc = std::chrono::system_clock;

private:
    std::unique_ptr<SchedulerKernel<T>> fKernel;

    bool fProcessing;

    T fPrintProgressModulo;

    WallTimeStopwatch<double> fWallTimeStopwatch;
    CPUTimeStopwatch<double> fCPUTimeStopwatch;
    double fRunWallTime;
    double fRunCPUTime;

    scsc::time_point fRunBeginSystemTime;
    scsc::time_point fRunEndSystemTime;

    std::string fRunName;
    std::string fTaskName;
};

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/Scheduler.inl"
