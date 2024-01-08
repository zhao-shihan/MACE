namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
SchedulerKernel<T>::SchedulerKernel(Task task) :
    fTask{task},
    fProcessingTask{},
    fNLocalProcessedTask{} {}

} // namespace MACE::inline Utility::MPIUtil
