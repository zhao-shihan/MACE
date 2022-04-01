#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class FirstBendSolenoid final : public IEntity {
public:
    FirstBendSolenoid() = default;
    ~FirstBendSolenoid() noexcept = default;
    FirstBendSolenoid(const FirstBendSolenoid&) = delete;
    FirstBendSolenoid& operator=(const FirstBendSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
