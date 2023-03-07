#pragma once

namespace MACE::Utility {

/// @brief Trivial derived class will Exactly comply with the constraints of
/// MACE::Utility::Concept::NonMoveable.
class NonMoveableBase {
protected:
    constexpr NonMoveableBase() noexcept = default;
    constexpr ~NonMoveableBase() noexcept = default;

    constexpr NonMoveableBase(const NonMoveableBase&) noexcept = delete;
    constexpr NonMoveableBase& operator=(const NonMoveableBase&) noexcept = delete;

    constexpr NonMoveableBase(NonMoveableBase&&) noexcept = delete;
    constexpr NonMoveableBase& operator=(NonMoveableBase&&) noexcept = delete;
};

} // namespace MACE::Utility
