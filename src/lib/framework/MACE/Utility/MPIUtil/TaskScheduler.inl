namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
TaskScheduler<T>::TaskScheduler() :
    NonMoveableBase{},
    fProcessing{},
    fTask{},
    fProcessingTask{},
    fNLocalProcessedTask{},
    fMemory{},
    fWindow{},
    fPrintProgressModulo{},
    fWallTimeStopwatch{},
    fCPUTimeStopwatch{},
    fRunWallTime{},
    fRunCPUTime{},
    fRunBeginSystemTime{},
    fRunEndSystemTime{},
    fRunName{"Run"},
    fTaskName{"Task"} {
    MPI_Info info;
    MPI_Info_create(&info);
    MPI_Info_set(info,
                 "accumulate_ops",
                 "same_op");
    MPI_Info_set(info,
                 "accumulate_ordering",
                 "none");
    MPI_Info_set(info,
                 "same_disp_unit",
                 "true");
    MPI_Win_allocate(Env::MPIEnv::Instance().AtCommWorldMaster() ? sizeof(T) : 0,
                     sizeof(T),
                     info,
                     MPI_COMM_WORLD,
                     &fMemory,
                     &fWindow);
    MPI_Win_fence(MPI_MODE_NOSTORE | MPI_MODE_NOPUT | MPI_MODE_NOPRECEDE | MPI_MODE_NOSUCCEED,
                  fWindow);
    MPI_Info_free(&info);
}

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
TaskScheduler<T>::~TaskScheduler() {
    assert(fProcessingTask <= fTask.last);
    MPI_Win_free(&fWindow);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::AssignTask(T first, T last) -> void {
    if (last < first) { throw std::invalid_argument{"last < first not allowed"}; }
    if (Env::MPIEnv::Instance().CommWorldSize() < NTask()) { fmt::println(stderr, "Warning: size of MPI_COMM_WORLD < number of tasks"); }
    fTask = {first, last};
    Reset();
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::Reset() -> void {
    fProcessingTask = fTask.first;
    fNLocalProcessedTask = 0;
    if (Env::MPIEnv::Instance().AtCommWorldMaster()) {
        *fMemory = fTask.first;
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::Next() -> std::optional<T> {
    assert(fProcessingTask <= fTask.last);
    if (fProcessingTask == fTask.last) { return std::nullopt; }

    if (fNLocalProcessedTask == 0) {
        PreRunAction();
    }

    constexpr T one{1};
    MPI_Win_lock(MPI_LOCK_EXCLUSIVE,
                 0,
                 0,
                 fWindow);
    MPI_Fetch_and_op(&one,
                     &fProcessingTask,
                     DataType<T>(),
                     0,
                     0,
                     MPI_SUM,
                     fWindow);
    MPI_Win_unlock(0,
                   fWindow);
    if (fProcessingTask > fTask.last) { fProcessingTask = fTask.last; } // note: fetch-and-add over last is possible

    if (fNLocalProcessedTask > 0) {
        TaskAction();
    }
    ++fNLocalProcessedTask;

    if (fProcessingTask < fTask.last) {
        return fProcessingTask;
    }

    PostRunAction();
    return std::nullopt;
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PreRunAction() -> void {
    fProcessing = true;
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    MPI_Win_fence(mpiEnv.AtCommWorldMaster() ?
                      MPI_MODE_NOPRECEDE :
                      MPI_MODE_NOSTORE | MPI_MODE_NOPUT | MPI_MODE_NOPRECEDE,
                  fWindow);
    fRunBeginSystemTime = scsc::now();
    fWallTimeStopwatch = {};
    fCPUTimeStopwatch = {};
    if (fPrintProgressModulo >= 0 and
        mpiEnv.AtCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
        PreRunReport();
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::TaskAction() const -> void {
    if (fPrintProgressModulo > 0 and fProcessingTask % fPrintProgressModulo == 0) {
        if (Env::MPIEnv::Instance().GetVerboseLevel() >= Env::VL::Error) {
            TaskReport();
        }
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PostRunAction() -> void {
    fRunWallTime = fWallTimeStopwatch.SecondsElapsed();
    fRunCPUTime = fCPUTimeStopwatch.SecondsUsed();
    fRunEndSystemTime = scsc::now();
    MPI_Win_fence(MPI_MODE_NOSTORE | MPI_MODE_NOPUT | MPI_MODE_NOSUCCEED,
                  fWindow);
    fProcessing = false;
    if (fPrintProgressModulo >= 0) {
        if (const auto& mpiEnv{Env::MPIEnv::Instance()};
            mpiEnv.AtCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
            PostRunReport();
        }
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PreRunReport() const -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("-------------------------------------------------------------------------------\n"
               " {:%FT%T%z} > {} has started on {} ranks\n"
               "-------------------------------------------------------------------------------\n",
               fmt::localtime(scsc::to_time_t(fRunBeginSystemTime)), fRunName, mpiEnv.CommWorldSize());
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::TaskReport() const -> void {
    using namespace std::string_literals;
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    const auto t{fWallTimeStopwatch.SecondsElapsed()};
    const auto nUp{static_cast<double>(fProcessingTask)};
    const auto nLow{nUp > mpiEnv.CommWorldSize() ? nUp - mpiEnv.CommWorldSize() : 1};
    const auto eta{t * (NTask() * Math::MidPoint(1 / nUp, 1 / nLow) - 1)};
    // const auto etaError{3 * t * mpiEnv.CommWorldSize() * NTask() / (2 * nUp * nLow)};
    const auto nMean{Math::MidPoint(nLow, nUp)};
    const auto progress{nMean / NTask()};
    fmt::print("Rank{}> {:%FT%T%z} > {} {} has started\n"
               "Rank{}>   Est. rem. time: {}  Progress: {}/{} ({:.4}%)\n",
               mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), fTaskName, fProcessingTask,
               mpiEnv.CommWorldRank(), SToDHMS(eta), nMean, NTask(), 100 * progress);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::PostRunReport() const -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("-------------------------------------------------------------------------------\n"
               " {:%FT%T%z} > {} has ended on {} ranks\n"
               "   Start time: {:%FT%T%z}\n"
               "    Wall time: {:.3f} seconds{}\n"
               "-------------------------------------------------------------------------------\n",
               fmt::localtime(scsc::to_time_t(fRunEndSystemTime)), fRunName, mpiEnv.CommWorldSize(),
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
