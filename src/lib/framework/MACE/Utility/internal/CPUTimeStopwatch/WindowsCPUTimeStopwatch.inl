namespace MACE::inline Utility::internal {

template<typename ATime>
CPUTimeStopwatch<ATime>::CPUTimeStopwatch() noexcept :
    fCurrentProcess{GetCurrentProcess()},
    fT0{ClockIn100ns()} {}

template<typename ATime>
auto CPUTimeStopwatch<ATime>::ClockIn100ns() const noexcept -> ULARGE_INTEGER {
    FILETIME tCreation;
    FILETIME tExit;
    FILETIME tKernel;
    FILETIME tUser;
    GetProcessTimes(fCurrentProcess, &tCreation, &tExit, &tKernel, &tUser);
    ULARGE_INTEGER t;
    static_assert(sizeof(FILETIME) == sizeof(ULARGE_INTEGER));
    std::memcpy(&t, &tUser, sizeof(FILETIME));
    return t;
}

} // namespace MACE::inline Utility::internal
