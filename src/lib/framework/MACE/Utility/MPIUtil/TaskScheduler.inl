namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
TaskScheduler<T>::TaskScheduler() :
    NonMoveableBase{},
    fTask{},
    fProcessing{},
    fProcessingTask{},
    fNLocalProcessedTask{},
    fStep{Env::MPIEnv::Instance().CommWorldSize()},
    fPrintProgressModulo{Env::MPIEnv::Instance().Parallel() ? 10 * Env::MPIEnv::Instance().CommWorldSize() + 1 : 10},
    fWallTimeStopwatch{},
    fCPUTimeStopwatch{},
    fRunWallTime{},
    fRunCPUTime{},
    fRunBeginSystemTime{},
    fRunEndSystemTime{},
    fRunName{"Run"},
    fTaskName{"Task"} {}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
TaskScheduler<T>::TaskScheduler(T size) :
    TaskScheduler{0, size} {}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
TaskScheduler<T>::TaskScheduler(T first, T last) :
    TaskScheduler{} {
    AssignTask(first, last);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::AssignTask(T first, T last) -> void {
    if (fProcessing) { throw std::logic_error{"Assign task during processing is not allowed"}; }
    if (last < first) { throw std::invalid_argument{"last < first is not allowed"}; }
    if (Deficient()) { fmt::println(stderr, "Warning: size of MPI_COMM_WORLD < number of tasks"); }
    fTask = {first, last};
    Reset();
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::Reset() -> void {
    fProcessing = false;
    fProcessingTask = fTask.first + Env::MPIEnv::Instance().CommWorldRank();
    fNLocalProcessedTask = 0;
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::Next() -> std::optional<T> {
    if (not fProcessing) [[unlikely]] {
        if (fProcessingTask == fTask.last) { return std::nullopt; }
        PreRunAction();
        fProcessing = true;
    } else {
        const auto processedTask{fProcessingTask};
        fProcessingTask = std::min(fProcessingTask + fStep, fTask.last);
        ++fNLocalProcessedTask;
        PostTaskAction(processedTask);
    }
    if (fProcessingTask != fTask.last) [[likely]] {
        return fProcessingTask;
    }
    fProcessing = false;
    PostRunAction();
    return std::nullopt;
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PreRunAction() -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    MPI_Barrier(MPI_COMM_WORLD);
    fRunBeginSystemTime = scsc::now();
    fWallTimeStopwatch = {};
    fCPUTimeStopwatch = {};
    if (fPrintProgressModulo >= 0 and
        mpiEnv.OnCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
        PreRunReport();
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PostTaskAction(T iEnded) const -> void {
    if (fPrintProgressModulo > 0 and iEnded % fPrintProgressModulo == 0) {
        if (Env::MPIEnv::Instance().GetVerboseLevel() >= Env::VL::Error) {
            TaskReport(iEnded);
        }
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PostRunAction() -> void {
    fRunWallTime = fWallTimeStopwatch.SecondsElapsed();
    fRunCPUTime = fCPUTimeStopwatch.SecondsUsed();
    fRunEndSystemTime = scsc::now();
    MPI_Barrier(MPI_COMM_WORLD);
    if (fPrintProgressModulo >= 0) {
        if (const auto& mpiEnv{Env::MPIEnv::Instance()};
            mpiEnv.OnCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
            PostRunReport();
        }
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PreRunReport() const -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("-------------------------------------------------------------------------------\n"
               " {:%FT%T%z} > {} has started on {} process{}\n"
               "-------------------------------------------------------------------------------\n",
               fmt::localtime(scsc::to_time_t(fRunBeginSystemTime)), fRunName, mpiEnv.CommWorldSize(), mpiEnv.Parallel() ? "es" : "");
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::TaskReport(T iEnded) const -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    const auto progress{static_cast<double>(NProcessedTask()) / NTask()};
    const auto eta{(1 / progress - 1) * fWallTimeStopwatch.SecondsElapsed()};
    fmt::print("MPI{}> {:%FT%T%z} > {} {} has ended\n"
               "MPI{}>   Est. rem. time: {}  Progress: {} | {}/{} | {:.4}%\n",
               mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), fTaskName, iEnded,
               mpiEnv.CommWorldRank(), fNLocalProcessedTask > 10 ? SToDHMS(eta) : "N/A", fNLocalProcessedTask, NProcessedTask(), NTask(), 100 * progress);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PostRunReport() const -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("-------------------------------------------------------------------------------\n"
               " {:%FT%T%z} > {} has ended on {} process{}\n"
               "   Start time: {:%FT%T%z}\n"
               "    Wall time: {:.3f} seconds{}\n"
               "-------------------------------------------------------------------------------\n",
               fmt::localtime(scsc::to_time_t(fRunEndSystemTime)), fRunName, mpiEnv.CommWorldSize(), mpiEnv.Parallel() ? "es" : "",
               fmt::localtime(scsc::to_time_t(fRunBeginSystemTime)),
               fRunWallTime, fRunWallTime <= 60 ? "" : " (" + SToDHMS(fRunWallTime) + ')');
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::SToDHMS(double s) -> std::string {
    const auto totalSeconds{std::llround(s)};
    const auto div86400{std2b::div(totalSeconds, 86400ll)};
    const auto div3600{std2b::div(div86400.rem, 3600ll)};
    const auto div60{std2b::div(div3600.rem, 60ll)};
    const auto& [day, hour, minute, second]{std::tie(div86400.quot, div3600.quot, div60.quot, div60.rem)};
    if (day > 0) { return fmt::format("{}d {}h", day, hour); }
    if (hour > 0) { return fmt::format("{}h {}m", hour, minute); }
    if (minute > 0) { return fmt::format("{}m {}s", minute, second); }
    return fmt::format("{}s", second);
}

} // namespace MACE::inline Utility::MPIUtil
