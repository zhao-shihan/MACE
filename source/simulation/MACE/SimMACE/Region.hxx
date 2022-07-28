#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4Region.hh"

namespace MACE::SimMACE {

enum class RegionType {
    EMCalSensitive,
    DefaultSolid,
    DefaultGaseous,
    Shield,
    SolenoidOrMagnet,
    SpectrometerSensitive,
    Target,
    Vacuum,
    MCPSensitive
};

class Region final : public Utility::NonMoveableBase,
                     public G4Region {
public:
    Region(const G4String& name, RegionType type);

    auto GetType() const { return fRegionType; }

private:
    const RegionType fRegionType;
};

} // namespace MACE::SimMACE
