#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::ThirdTransportSolenoid final :
    public MACE::Geometry::Interface::Entity {
public:
    ThirdTransportSolenoid() = default;
    ~ThirdTransportSolenoid() noexcept = default;
    ThirdTransportSolenoid(const ThirdTransportSolenoid&) = delete;
    ThirdTransportSolenoid& operator=(const ThirdTransportSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
