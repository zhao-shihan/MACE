#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "G4Region.hh"

namespace MACE::inline Simulation::SimMACE {

enum class RegionType {
    CDCFieldWire,
    CDCSenseWire,
    DefaultGaseous,
    DefaultSolid,
    EMCSensitive,
    MCPSensitive,
    Shield,
    SolenoidOrMagnet,
    SpectrometerSensitive,
    Target,
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

} // namespace MACE::inline Simulation::SimMACE
