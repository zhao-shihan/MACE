#pragma once

#include <chrono>
#include <concepts>
#include <limits>

namespace MACE::Utility::internal {

template<std::floating_point ATime>
    requires(std::numeric_limits<ATime>::digits >= std::numeric_limits<double>::digits)
class Timer {
private:
    using sc = std::chrono::steady_clock;
    using s = std::chrono::duration<ATime, std::ratio<1>>;
    using ms = std::chrono::duration<ATime, std::milli>;
    using us = std::chrono::duration<ATime, std::micro>;
    using ns = std::chrono::duration<ATime, std::nano>;

public:
    Timer() noexcept;

    void Reset() noexcept { fT0 = sc::now(); }
    auto SecondsElapsed() noexcept { s(sc::now() - fT0).count(); }
    auto MillisecondsElapsed() noexcept { ms(sc::now() - fT0).count(); }
    auto MicrosecondsElapsed() noexcept { us(sc::now() - fT0).count(); }
    auto NanosecondsElapsed() noexcept { ns(sc::now() - fT0).count(); }

private:
    sc::time_point fT0;
};

} // namespace MACE::Utility::internal

#include "MACE/Utility/internal/Timer/Timer4Fallback.inl"
