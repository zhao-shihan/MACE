#pragma once

#include <chrono>

namespace MACE::inline Utility::internal {

template<typename ATime>
class WallTimeStopwatch {
private:
    using sc = std::chrono::steady_clock;
    using s = std::chrono::duration<ATime, std::ratio<1>>;
    using ms = std::chrono::duration<ATime, std::milli>;
    using us = std::chrono::duration<ATime, std::micro>;
    using ns = std::chrono::duration<ATime, std::nano>;

public:
    WallTimeStopwatch() noexcept;

    auto SecondsElapsed() const noexcept -> auto { s(sc::now() - fT0).count(); }
    auto MillisecondsElapsed() const noexcept -> auto { ms(sc::now() - fT0).count(); }
    auto MicrosecondsElapsed() const noexcept -> auto { us(sc::now() - fT0).count(); }
    auto NanosecondsElapsed() const noexcept -> auto { ns(sc::now() - fT0).count(); }

private:
    sc::time_point fT0;
};

} // namespace MACE::inline Utility::internal

#include "MACE/Utility/internal/WallTimeStopwatch/FallbackWallTimeStopwatch.inl"
