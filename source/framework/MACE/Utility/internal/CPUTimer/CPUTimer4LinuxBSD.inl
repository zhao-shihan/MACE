namespace MACE::Utility::internal {

template<typename ATime>
CPUTimer<ATime>::CPUTimer() noexcept :
    fT0() {
    Reset();
}

template<typename ATime>
ATime CPUTimer<ATime>::NanosecondsUsed() noexcept {
    struct timespec t;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
    return static_cast<ATime>(t.tv_sec - fT0.tv_sec) * 1'000'000'000 +
           static_cast<ATime>(t.tv_nsec - fT0.tv_nsec);
}

} // namespace MACE::Utility::internal
