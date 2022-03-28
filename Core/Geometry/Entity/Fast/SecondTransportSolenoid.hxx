#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SecondTransportSolenoid final : public IEntity {
public:
    SecondTransportSolenoid() = default;
    ~SecondTransportSolenoid() noexcept = default;
    SecondTransportSolenoid(const SecondTransportSolenoid&) = delete;
    SecondTransportSolenoid& operator=(const SecondTransportSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
