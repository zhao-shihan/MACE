namespace MACE::inline Extension::MPIX {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
auto Scheduler<T>::Reset() -> void {
    fExecutingTask = fTask.first;
    fNLocalExecutedTask = 0;
}

} // namespace MACE::inline Extension::MPIX
