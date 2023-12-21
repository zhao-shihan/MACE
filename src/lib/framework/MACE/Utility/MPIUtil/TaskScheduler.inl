namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
TaskScheduler<T>::TaskScheduler() :
    NonMoveableBase{},
    fTask{},
    fProcessing{},
    fNLocalProcessed{},
    fMemory{},
    fWindow{} {
    MPI_Info info;
    MPI_Info_create(&info);
    MPI_Info_set(info,
                 "no_locks",
                 "true");
    MPI_Info_set(info,
                 "accumulate_ops",
                 "same_op");
    MPI_Info_set(info,
                 "accumulate_ordering",
                 "none");
    MPI_Info_set(info,
                 "same_size",
                 "true");
    MPI_Info_set(info,
                 "same_disp_unit",
                 "true");
    MPI_Win_allocate(sizeof(T),
                     sizeof(T),
                     info,
                     MPI_COMM_WORLD,
                     &fMemory,
                     &fWindow);
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
    assert(fProcessing <= fTask.last);
    MPI_Win_fence(MPI_MODE_NOSUCCEED,
                  fWindow);
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
    fProcessing = fTask.first;
    fNLocalProcessed = 0;
    MPI_Win_fence(MPI_MODE_NOSUCCEED,
                  fWindow);
    *fMemory = fTask.first;
    MPI_Win_fence(MPI_MODE_NOPRECEDE,
                  fWindow);
}

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto TaskScheduler<T>::Next() -> std::optional<T> {
    assert(fProcessing <= fTask.last);
    if (fProcessing == fTask.last) { return std::nullopt; }
    constexpr T one{1};
    MPI_Fetch_and_op(&one,
                     &fProcessing,
                     DataType<T>(),
                     0,
                     0,
                     MPI_SUM,
                     fWindow);
    if (fProcessing > fTask.last) { fProcessing = fTask.last; } // note: fetch-and-add over last is possible
    if (fProcessing == fTask.last) { return std::nullopt; }
    ++fNLocalProcessed;
    return fProcessing;
}

} // namespace MACE::inline Utility::MPIUtil
