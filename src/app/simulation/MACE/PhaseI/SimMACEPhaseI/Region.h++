#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "G4Region.hh"

namespace MACE::PhaseI::SimMACEPhaseI {

enum struct RegionType {
    DefaultGaseous,
    DefaultSolid,
    EMCSensitive,
    Shield,
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

} // namespace MACE::PhaseI::SimMACEPhaseI
