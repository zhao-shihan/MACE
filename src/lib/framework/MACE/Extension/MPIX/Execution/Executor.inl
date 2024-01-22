namespace MACE::inline Extension::MPIX::inline Execution {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
template<template<typename> typename S>
    requires std::derived_from<S<T>, Scheduler<T>>
Executor<T>::Executor(ScheduleBy<S>) :
    fScheduler{std::make_unique_for_overwrite<S<T>>()},
    fExecuting{},
    fPrintProgressModulo{Env::MPIEnv::Instance().Parallel() ? 10 * Env::MPIEnv::Instance().CommWorldSize() + 1 : 10},
    fExecutionName{"Execution"},
    fTaskName{"Task"},
    fExecutionBeginSystemTime{},
    fWallTimeStopwatch{},
    fCPUTimeStopwatch{},
    fExecutionWallTimeAndCPUTime{},
    fExecutionWallTime{fExecutionWallTimeAndCPUTime[0]},
    fExecutionCPUTime{fExecutionWallTimeAndCPUTime[1]},
    fExecutionWallTimeAndCPUTimeOfAllProcessKeptByMaster{},
    fNLocalExecutedTaskOfAllProcessKeptByMaster{} {
    if (const auto& mpiEnv{Env::MPIEnv::Instance()};
        mpiEnv.OnCommWorldMaster()) {
        fExecutionWallTimeAndCPUTimeOfAllProcessKeptByMaster.resize(mpiEnv.CommWorldSize());
        fNLocalExecutedTaskOfAllProcessKeptByMaster.resize(mpiEnv.CommWorldSize());
    }
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
template<template<typename> typename S>
    requires std::derived_from<S<T>, Scheduler<T>>
Executor<T>::Executor(typename Scheduler<T>::Task task, ScheduleBy<S>) :
    Executor{ScheduleBy<S>{}} {
    AssignTask(task);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
template<template<typename> typename S>
    requires std::derived_from<S<T>, Scheduler<T>>
Executor<T>::Executor(T size, ScheduleBy<S>) : // clang-format off
    Executor{{0, size}, ScheduleBy<S>{}} {} // clang-format on

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
template<template<typename> typename S>
    requires std::derived_from<S<T>, Scheduler<T>>
Executor<T>::Executor(T first, T last, ScheduleBy<S>) : // clang-format off
    Executor{{first, last}, ScheduleBy<S>{}} {} // clang-format on

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
template<template<typename> typename AScheduler>
    requires std::derived_from<AScheduler<T>, Scheduler<T>>
auto Executor<T>::SwitchScheduler() -> void {
    if (fExecuting) { throw std::logic_error{"switch scheduler kernel during processing"}; }
    auto task{std::move(fScheduler->fTask)};
    fScheduler = std::make_unique_for_overwrite<AScheduler<T>>();
    fScheduler->fTask = std::move(task);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
auto Executor<T>::AssignTask(typename Scheduler<T>::Task task) -> void {
    if (fExecuting) { throw std::logic_error{"assign task during processing"}; }
    if (task.last < task.first) { throw std::invalid_argument{"last < first"}; }
    if (Env::MPIEnv::Instance().CommWorldSize() > task.last - task.first) { throw std::runtime_error{"size of MPI_COMM_WORLD > number of tasks"}; }
    fScheduler->fTask = task;
    fScheduler->Reset();
    assert(ExecutingTask() == Task().first);
    assert(NLocalExecutedTask() == 0);
    assert(NExecutedTask() == 0);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
auto Executor<T>::Execute(std::invocable<T> auto&& Func) -> T {
    fScheduler->Reset();
    fExecuting = true;
    fScheduler->PreLoopAction();
    MPI_Barrier(MPI_COMM_WORLD);
    fExecutionBeginSystemTime = scsc::now();
    fWallTimeStopwatch = {};
    fCPUTimeStopwatch = {};
    PreLoopReport();
    while (ExecutingTask() != Task().last) {
        fScheduler->PreTaskAction();
        const auto taskID{ExecutingTask()};
        assert(taskID <= Task().last);
        Func(taskID);
        ++fScheduler->fNLocalExecutedTask;
        fScheduler->PostTaskAction();
        PostTaskReport(taskID);
    }
    fExecutionWallTime = fWallTimeStopwatch.SecondsElapsed();
    fExecutionCPUTime = fCPUTimeStopwatch.SecondsUsed();
    std::array<MPI_Request, 2> gatherRequest;
    auto& [gatherTimeRequest, gatherNLocalExecutedTaskRequest]{gatherRequest};
    MPI_Igather(fExecutionWallTimeAndCPUTime.data(),                         // sendbuf
                2,                                                           // sendcount
                MPI_DOUBLE,                                                  // sendtype
                fExecutionWallTimeAndCPUTimeOfAllProcessKeptByMaster.data(), // recvbuf
                2,                                                           // recvcount
                MPI_DOUBLE,                                                  // recvtype
                0,                                                           // root
                MPI_COMM_WORLD,                                              // comm
                &gatherTimeRequest);                                         // request
    MPI_Igather(&fScheduler->fNLocalExecutedTask,                            // sendbuf
                1,                                                           // sendcount
                DataType<T>(),                                               // sendtype
                fNLocalExecutedTaskOfAllProcessKeptByMaster.data(),          // recvbuf
                1,                                                           // recvcount
                DataType<T>(),                                               // recvtype
                0,                                                           // root
                MPI_COMM_WORLD,                                              // comm
                &gatherNLocalExecutedTaskRequest);                           // request
    fScheduler->PostLoopAction();
    fExecuting = false;
    MPI_Waitall(gatherRequest.size(), // count
                gatherRequest.data(), // array_of_requests
                MPI_STATUSES_IGNORE); // array_of_statuses
    PostLoopReport();
    return NLocalExecutedTask();
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
auto Executor<T>::PrintExecutionSummary() const -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (not(mpiEnv.OnCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error)) { return; }
    if (fExecuting and mpiEnv.GetVerboseLevel() >= Env::VL::Warning) { fmt::print(stderr, "Execution summary not available for now."); }
    fmt::println("+------------------+--------------> Summary <-------------+-------------------+\n"
                 "| Rank in world    | Executed          | Wall time (s)    | CPU time (s)      |\n"
                 "+------------------+-------------------+------------------+-------------------+");
    for (int rank{}; rank < mpiEnv.CommWorldSize(); ++rank) {
        const auto& executed{fNLocalExecutedTaskOfAllProcessKeptByMaster[rank]};
        const auto& [wallTime, cpuTime]{fExecutionWallTimeAndCPUTimeOfAllProcessKeptByMaster[rank]};
        fmt::println("| {:16} | {:17} | {:16.3f} | {:17.3f} |", rank, executed, wallTime, cpuTime);
    }
    fmt::println("+------------------+--------------> Summary <-------------+-------------------+");
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
auto Executor<T>::PreLoopReport() const -> void {
    if (fPrintProgressModulo < 0) { return; }
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (not(mpiEnv.OnCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error)) { return; }
    fmt::print("+----------------------------------> Start <----------------------------------+\n"
               "| {:75} |\n"
               "+----------------------------------> Start <----------------------------------+\n",
               fmt::format("{:%FT%T%z} > {} has started on {} process{}",
                           fmt::localtime(scsc::to_time_t(fExecutionBeginSystemTime)), fExecutionName, mpiEnv.CommWorldSize(), mpiEnv.Parallel() ? "es" : ""));
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
auto Executor<T>::PostTaskReport(T iEnded) const -> void {
    if (not(fPrintProgressModulo > 0 and NExecutedTask() % fPrintProgressModulo == 0)) { return; }
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (mpiEnv.GetVerboseLevel() < Env::VL::Error) { return; }
    const auto progress{static_cast<double>(NExecutedTask()) / NTask()};
    const auto eta{(1 / progress - 1) * fWallTimeStopwatch.SecondsElapsed()};
    fmt::print("MPI{}> {:%FT%T%z} > {} {} has ended\n"
               "MPI{}>   Est. rem. time: {}  Progress: {} | {}/{} | {:.4}%\n",
               mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), fTaskName, iEnded,
               mpiEnv.CommWorldRank(), NLocalExecutedTask() > 10 ? SToDHMS(eta) : "N/A", NLocalExecutedTask(), NExecutedTask(), NTask(), 100 * progress);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
auto Executor<T>::PostLoopReport() const -> void {
    if (fPrintProgressModulo < 0) { return; }
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (not(mpiEnv.OnCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error)) { return; }
    const auto now{scsc::now()};
    double maxWallTime{};
    double totalCpuTime{};
    for (auto&& [wallTime, cpuTime] : std::as_const(fExecutionWallTimeAndCPUTimeOfAllProcessKeptByMaster)) {
        if (wallTime > maxWallTime) { maxWallTime = wallTime; }
        totalCpuTime += cpuTime;
    }
    fmt::print("+-----------------------------------> End <-----------------------------------+\n"
               "| {:75} |\n"
               "| {:75} |\n"
               "| {:75} |\n"
               "| {:75} |\n"
               "+-----------------------------------> End <-----------------------------------+\n",
               fmt::format("{:%FT%T%z} > {} has ended on {} process{}", fmt::localtime(scsc::to_time_t(now)), fExecutionName, mpiEnv.CommWorldSize(), mpiEnv.Parallel() ? "es" : ""),
               fmt::format("  Start time: {:%FT%T%z}", fmt::localtime(scsc::to_time_t(fExecutionBeginSystemTime))),
               fmt::format("   Wall time: {:.3f} seconds{}", maxWallTime, maxWallTime <= 60 ? "" : " (" + SToDHMS(maxWallTime) + ')'),
               fmt::format("    CPU time: {:.3f} seconds{}", totalCpuTime, totalCpuTime <= 60 ? "" : " (" + SToDHMS(totalCpuTime) + ')'));
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(short))
auto Executor<T>::SToDHMS(double s) -> std::string {
    const auto totalSeconds{std::llround(s)};
    const auto div86400{std23::div(totalSeconds, 86400ll)};
    const auto div3600{std23::div(div86400.rem, 3600ll)};
    const auto div60{std23::div(div3600.rem, 60ll)};
    const auto& [day, hour, minute, second]{std::tie(div86400.quot, div3600.quot, div60.quot, div60.rem)};
    if (day > 0) { return fmt::format("{}d {}h {}m", day, hour, minute); }
    if (hour > 0) { return fmt::format("{}h {}m", hour, minute); }
    if (minute > 0) { return fmt::format("{}m {}s", minute, second); }
    return fmt::format("{}s", second);
}

} // namespace MACE::inline Extension::MPIX::inline Execution
