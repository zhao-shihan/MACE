#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SecondTransportSolenoid final :
    public MACE::Geometry::Interface::Entity {
public:
    SecondTransportSolenoid() = default;
    ~SecondTransportSolenoid() noexcept = default;
    SecondTransportSolenoid(const SecondTransportSolenoid&) = delete;
    SecondTransportSolenoid& operator=(const SecondTransportSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
