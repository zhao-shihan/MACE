namespace MACE::inline Utility::MPIUtil {

template<std::integral T>
StaticTaskScheduler<T>::StaticTaskScheduler() :
    TaskScheduler<T>{} {}

template<std::integral T>
StaticTaskScheduler<T>::StaticTaskScheduler(T size) :
    TaskScheduler<T>{size} {}

template<std::integral T>
StaticTaskScheduler<T>::StaticTaskScheduler(T first, T last) :
    TaskScheduler<T>{first, last} {}

template<std::integral T>
auto StaticTaskScheduler<T>::PreRunAction() -> void {
    this->fProcessingTask = this->fTask.first + Env::MPIEnv::Instance().CommWorldRank();
}

template<std::integral T>
auto StaticTaskScheduler<T>::PostTaskAction() -> void {
    this->fProcessingTask += Env::MPIEnv::Instance().CommWorldSize();
    if (this->fProcessingTask > this->fTask.last) [[unlikely]] {
        this->fProcessingTask = this->fTask.last;
    }
}

} // namespace MACE::inline Utility::MPIUtil
