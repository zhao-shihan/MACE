namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
    requires(Concept::MPIPredefined<T> and sizeof(T) >= sizeof(int))
SchedulerKernel<T>::SchedulerKernel(T first, T last) :
    fTask{first, last},
    fProcessingTask{},
    fNLocalProcessedTask{} {}

} // namespace MACE::inline Utility::MPIUtil
