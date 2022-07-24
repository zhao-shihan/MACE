#pragma once

namespace MACE::Utility {

class NonCopyableBase {
protected:
    constexpr NonCopyableBase() = default;
    constexpr ~NonCopyableBase() = default;
    constexpr NonCopyableBase(const NonCopyableBase&) = delete;
    constexpr NonCopyableBase& operator=(const NonCopyableBase&) = delete;
};

} // namespace MACE::Utility
