#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "G4Region.hh"

namespace MACE::SimEMC {

enum struct RegionType {
    EMCSensitive,
    MCPSensitive,
    SolenoidOrMagnet,
    Shield,
    Tunnel,
    Vacuum
};

class Region final : public NonMoveableBase,
                     public G4Region {
public:
    Region(const G4String& name, RegionType type);

    const auto& Type() const { return fRegionType; }

private:
    const RegionType fRegionType;
};

} // namespace MACE::SimEMC
