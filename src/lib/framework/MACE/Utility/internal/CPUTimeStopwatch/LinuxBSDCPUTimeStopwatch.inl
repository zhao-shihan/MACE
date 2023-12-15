namespace MACE::inline Utility::internal {

template<typename ATime>
CPUTimeStopwatch<ATime>::CPUTimeStopwatch() noexcept :
    fT0{} {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fT0);
}

template<typename ATime>
auto CPUTimeStopwatch<ATime>::NanosecondsUsed() const noexcept -> ATime {
    std::timespec t;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
    return static_cast<ATime>(t.tv_sec - fT0.tv_sec) * 1'000'000'000 +
           static_cast<ATime>(t.tv_nsec - fT0.tv_nsec);
}

} // namespace MACE::inline Utility::internal
