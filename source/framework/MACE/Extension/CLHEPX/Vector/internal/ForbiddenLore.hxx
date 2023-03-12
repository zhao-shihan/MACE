#pragma once

namespace MACE::inline Extension::CLHEPX::Vector::internal {

template<auto APointerToMember>
class ForbiddenLore;

template<typename AMember, class AClass, AMember AClass::*APointerToMember>
class ForbiddenLore<APointerToMember> {
    friend constexpr AMember& ForbiddenGet(AClass& object) { return object.*APointerToMember; }
    friend constexpr const AMember& ForbiddenGet(const AClass& object) { return object.*APointerToMember; }
    friend constexpr AMember&& ForbiddenGet(AClass&& object) = delete;
    friend constexpr const AMember&& ForbiddenGet(const AClass&& object) = delete;
};

} // namespace MACE::inline Extension::CLHEPX::Vector::internal
