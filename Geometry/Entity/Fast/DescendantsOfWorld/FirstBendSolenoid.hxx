#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::FirstBendSolenoid final :
    public MACE::Geometry::Interface::Entity {
public:
    FirstBendSolenoid() = default;
    ~FirstBendSolenoid() noexcept = default;
    FirstBendSolenoid(const FirstBendSolenoid&) = delete;
    FirstBendSolenoid& operator=(const FirstBendSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
