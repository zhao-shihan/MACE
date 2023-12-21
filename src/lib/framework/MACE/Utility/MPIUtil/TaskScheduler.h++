#pragma once

#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/Concept/MPIPredefined.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Utility/CPUTimeStopwatch.h++"
#include "MACE/Utility/MPIUtil/DataType.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/WallTimeStopwatch.h++"

#include "mpi.h"

#include "fmt/chrono.h"
#include "fmt/format.h"

#include <cassert>
#include <chrono>
#include <cmath>
#include <concepts>
#include <cstdio>
#include <optional>
#include <stdexcept>
#include <tuple>

namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
class TaskScheduler : public NonMoveableBase {
public:
    TaskScheduler();
    explicit TaskScheduler(T size);
    TaskScheduler(T first, T last);
    ~TaskScheduler();

    auto AssignTask(T size) -> void { AssignTask(0, size); }
    auto AssignTask(T first, T last) -> void;
    auto Reset() -> void;
    auto PrintProgressModulo(T mod) -> void { fPrintProgressModulo = mod; }
    auto RunName(std::string name) { fRunName = std::move(name); }
    auto TaskName(std::string name) { fTaskName = std::move(name); }

    auto Processing() const -> bool { return fProcessing; }
    auto Task() const -> const auto& { return fTask; }
    auto NTask() const -> T { return fTask.last - fTask.first; }

    auto Next() -> std::optional<T>;
    auto ProcessingTask() const -> T { return fProcessingTask; }
    auto NProcessedTask() const -> T { return ProcessingTask() - fTask.first; }
    auto NLocalProcessedTask() const -> T { return fNLocalProcessedTask; }

private:
    using scsc = std::chrono::system_clock;

    auto PreRunAction() -> void;
    auto TaskAction() const -> void;
    auto PostRunAction() -> void;

    auto PreRunReport() const -> void;
    auto TaskReport() const -> void;
    auto PostRunReport() const -> void;

    static auto SToDHMS(double s) -> std::string;

private:
    bool fProcessing;
    struct {
        T first;
        T last;
    } fTask;
    T fProcessingTask;
    T fNLocalProcessedTask;

    volatile T* fMemory;
    MPI_Win fWindow;

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

#include "MACE/Utility/MPIUtil/TaskScheduler.inl"
