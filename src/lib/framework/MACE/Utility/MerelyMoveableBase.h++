#pragma once

namespace MACE::inline Utility {

/// @brief Trivial derived class will Exactly comply with the constraints of
/// MACE::Concept::MerelyMoveable.
class MerelyMoveableBase {
protected:
    constexpr MerelyMoveableBase() noexcept = default;
    constexpr ~MerelyMoveableBase() noexcept = default;

    constexpr MerelyMoveableBase(const MerelyMoveableBase&) noexcept = delete;
    constexpr MerelyMoveableBase& operator=(const MerelyMoveableBase&) noexcept = delete;

    constexpr MerelyMoveableBase(MerelyMoveableBase&&) noexcept = default;
    constexpr MerelyMoveableBase& operator=(MerelyMoveableBase&&) noexcept = default;
};

} // namespace MACE::inline Utility
