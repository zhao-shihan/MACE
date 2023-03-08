#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class ThirdTransportSolenoid final : public IEntity {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
