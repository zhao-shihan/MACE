#pragma once

#include "Core/Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SecondBendSolenoid final : public IEntity {
public:
    SecondBendSolenoid() = default;
    ~SecondBendSolenoid() noexcept = default;
    SecondBendSolenoid(const SecondBendSolenoid&) = delete;
    SecondBendSolenoid& operator=(const SecondBendSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
