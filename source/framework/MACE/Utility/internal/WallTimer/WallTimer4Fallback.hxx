#pragma once

#include <chrono>

namespace MACE::Utility::internal {

template<typename ATime>
class WallTimer {
private:
    using sc = std::chrono::steady_clock;
    using s = std::chrono::duration<ATime, std::ratio<1>>;
    using ms = std::chrono::duration<ATime, std::milli>;
    using us = std::chrono::duration<ATime, std::micro>;
    using ns = std::chrono::duration<ATime, std::nano>;

public:
    WallTimer() noexcept;

    void Reset() noexcept { fT0 = sc::now(); }
    auto SecondsElapsed() const noexcept { s(sc::now() - fT0).count(); }
    auto MillisecondsElapsed() const noexcept { ms(sc::now() - fT0).count(); }
    auto MicrosecondsElapsed() const noexcept { us(sc::now() - fT0).count(); }
    auto NanosecondsElapsed() const noexcept { ns(sc::now() - fT0).count(); }

private:
    sc::time_point fT0;
};

} // namespace MACE::Utility::internal

#include "MACE/Utility/internal/WallTimer/WallTimer4Fallback.inl"
