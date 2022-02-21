#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SecondBendSolenoid final :
    public MACE::Geometry::Interface::Entity {
public:
    SecondBendSolenoid() = default;
    ~SecondBendSolenoid() noexcept = default;
    SecondBendSolenoid(const SecondBendSolenoid&) = delete;
    SecondBendSolenoid& operator=(const SecondBendSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
