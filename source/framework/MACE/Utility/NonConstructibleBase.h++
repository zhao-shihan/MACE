#pragma once

namespace MACE::inline Utility {

class NonConstructibleBase {
private:
    constexpr NonConstructibleBase() = delete;
};

} // namespace MACE::inline Utility
