#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class FirstTransportSolenoid final : public IEntity {
public:
    FirstTransportSolenoid() = default;
    ~FirstTransportSolenoid() noexcept = default;
    FirstTransportSolenoid(const FirstTransportSolenoid&) = delete;
    FirstTransportSolenoid& operator=(const FirstTransportSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
