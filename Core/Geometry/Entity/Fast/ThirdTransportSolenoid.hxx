#pragma once

#include "Core/Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class ThirdTransportSolenoid final : public IEntity {
public:
    ThirdTransportSolenoid() = default;
    ~ThirdTransportSolenoid() noexcept = default;
    ThirdTransportSolenoid(const ThirdTransportSolenoid&) = delete;
    ThirdTransportSolenoid& operator=(const ThirdTransportSolenoid&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
