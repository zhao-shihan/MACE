#pragma once

namespace MACE::inline Utility {

class NonConstructibleBase {
protected:
    constexpr NonConstructibleBase() = delete;
    constexpr ~NonConstructibleBase() = delete;
};

} // namespace MACE::inline Utility
