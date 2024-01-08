namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
Scheduler<T>::Scheduler() :
    fKernel{std::make_unique_for_overwrite<StaticSchedulerKernel<T>>()},
    fProcessing{},
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
Scheduler<T>::Scheduler(T size) :
    Scheduler{0, size} {}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
Scheduler<T>::Scheduler(T first, T last) :
    Scheduler{} {
    AssignTask(first, last);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::AssignTask(T first, T last) -> void {
    if (fProcessing) { throw std::logic_error{"Assign task during processing is not allowed"}; }
    if (last < first) { throw std::invalid_argument{"last < first is not allowed"}; }
    fKernel->fTask = {first, last};
    if (Deficient()) { fmt::println(stderr, "Warning: size of MPI_COMM_WORLD > number of tasks"); }
    Reset();
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::Reset() -> void {
    fKernel->fProcessingTask = Task().first;
    fKernel->fNLocalProcessedTask = 0;
    fProcessing = false;
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::Next() -> std::optional<T> {
    if (not fProcessing) [[unlikely]] {
        if (ProcessingTask() == Task().last) { return std::nullopt; }
        fKernel->PreRunAction();
        MPI_Barrier(MPI_COMM_WORLD);
        fRunBeginSystemTime = scsc::now();
        fWallTimeStopwatch = {};
        fCPUTimeStopwatch = {};
        PreRunReport();
        fProcessing = true;
    } else {
        ++fKernel->fNLocalProcessedTask;
        const auto processedTask{ProcessingTask()};
        fKernel->PostTaskAction();
        PostTaskReport(processedTask);
    }
    if (ProcessingTask() != Task().last) [[likely]] {
        fKernel->PreTaskAction();
        return ProcessingTask();
    }
    fProcessing = false;
    fRunWallTime = fWallTimeStopwatch.SecondsElapsed();
    fRunCPUTime = fCPUTimeStopwatch.SecondsUsed();
    fRunEndSystemTime = scsc::now();
    fKernel->PostRunAction();
    MPI_Barrier(MPI_COMM_WORLD);
    PostRunReport();
    return std::nullopt;
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::PreRunReport() const -> void {
    if (fPrintProgressModulo >= 0) {
        const auto& mpiEnv{Env::MPIEnv::Instance()};
        if (mpiEnv.OnCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
            fmt::print("-------------------------------------------------------------------------------\n"
                       " {:%FT%T%z} > {} has started on {} process{}\n"
                       "-------------------------------------------------------------------------------\n",
                       fmt::localtime(scsc::to_time_t(fRunBeginSystemTime)), fRunName, mpiEnv.CommWorldSize(), mpiEnv.Parallel() ? "es" : "");
        }
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::PostTaskReport(T iEnded) const -> void {
    if (fPrintProgressModulo > 0 and iEnded % fPrintProgressModulo == 0) {
        const auto& mpiEnv{Env::MPIEnv::Instance()};
        if (mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
            const auto progress{static_cast<double>(NProcessedTask()) / NTask()};
            const auto eta{(1 / progress - 1) * fWallTimeStopwatch.SecondsElapsed()};
            fmt::print("MPI{}> {:%FT%T%z} > {} {} has ended\n"
                       "MPI{}>   Est. rem. time: {}  Progress: {} | {}/{} | {:.4}%\n",
                       mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), fTaskName, iEnded,
                       mpiEnv.CommWorldRank(), NLocalProcessedTask() > 10 ? SToDHMS(eta) : "N/A", NLocalProcessedTask(), NProcessedTask(), NTask(), 100 * progress);
        }
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::PostRunReport() const -> void {
    if (fPrintProgressModulo >= 0) {
        const auto& mpiEnv{Env::MPIEnv::Instance()};
        if (mpiEnv.OnCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
            fmt::print("-------------------------------------------------------------------------------\n"
                       " {:%FT%T%z} > {} has ended on {} process{}\n"
                       "   Start time: {:%FT%T%z}\n"
                       "    Wall time: {:.3f} seconds{}\n"
                       "-------------------------------------------------------------------------------\n",
                       fmt::localtime(scsc::to_time_t(fRunEndSystemTime)), fRunName, mpiEnv.CommWorldSize(), mpiEnv.Parallel() ? "es" : "",
                       fmt::localtime(scsc::to_time_t(fRunBeginSystemTime)),
                       fRunWallTime, fRunWallTime <= 60 ? "" : " (" + SToDHMS(fRunWallTime) + ')');
        }
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::SToDHMS(double s) -> std::string {
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
