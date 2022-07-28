#pragma once

namespace MACE::Utility {

/// @brief Trivial derived class will Exactly comply with the constraints of
/// MACE::Utility::Concept::NonMoveable.
class NonMoveableBase {
protected:
    constexpr NonMoveableBase() = default;
    constexpr ~NonMoveableBase() = default;
    constexpr NonMoveableBase(const NonMoveableBase&) = delete;
    constexpr NonMoveableBase& operator=(const NonMoveableBase&) = delete;
    constexpr NonMoveableBase(NonMoveableBase&&) = delete;
    constexpr NonMoveableBase& operator=(NonMoveableBase&&) = delete;
};

} // namespace MACE::Utility
