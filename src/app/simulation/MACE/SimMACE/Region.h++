#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "G4Region.hh"

namespace MACE::SimMACE {

enum struct RegionType {
    CDCFieldWire,
    CDCSenseWire,
    CDCSensitive,
    DefaultGaseous,
    DefaultSolid,
    EMCSensitive,
    MCPSensitive,
    Shield,
    SolenoidOrMagnet,
    STCSensitive,
    Target,
    Vacuum
};

class Region final : public NonMoveableBase,
                     public G4Region {
public:
    Region(const G4String& name, RegionType type);

    auto Type() const -> auto { return fRegionType; }

private:
    const RegionType fRegionType;
};

} // namespace MACE::SimMACE
