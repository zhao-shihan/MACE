namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
auto StaticSchedulerKernel<T>::PreRunAction() -> void {
    this->fProcessingTask = this->fTask.first + Env::MPIEnv::Instance().CommWorldRank();
}

template<std::integral T>
auto StaticSchedulerKernel<T>::PostTaskAction() -> void {
    this->fProcessingTask += Env::MPIEnv::Instance().CommWorldSize();
    if (this->fProcessingTask > this->fTask.last) [[unlikely]] {
        this->fProcessingTask = this->fTask.last;
    }
}

} // namespace MACE::inline Utility::MPIUtil
