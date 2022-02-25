#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::FirstTransportSolenoid final :
    public MACE::Geometry::Interface::Entity {
public:
    FirstTransportSolenoid() = default;
    ~FirstTransportSolenoid() noexcept = default;
    FirstTransportSolenoid(const FirstTransportSolenoid&) = delete;
    FirstTransportSolenoid& operator=(const FirstTransportSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};