#pragma once

namespace MACE::Utility {

/// @brief Trivial derived class will Exactly comply with the constraints of
/// MACE::Utility::Concept::MerelyMoveable.
class MerelyMoveableBase {
protected:
    constexpr MerelyMoveableBase() = default;
    constexpr ~MerelyMoveableBase() = default;
    constexpr MerelyMoveableBase(const MerelyMoveableBase&) = delete;
    constexpr MerelyMoveableBase& operator=(const MerelyMoveableBase&) = delete;
    constexpr MerelyMoveableBase(MerelyMoveableBase&&) = default;
    constexpr MerelyMoveableBase& operator=(MerelyMoveableBase&&) = default;
};

} // namespace MACE::Utility
