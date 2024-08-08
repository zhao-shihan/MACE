#pragma once

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4Region.hh"

namespace MACE::PhaseI::SimMACEPhaseI {

enum struct RegionType {
    DefaultGaseous,
    DefaultSolid,
    ECalSensitive,
    Shield,
    Target,
    Vacuum
};

class Region final : public Mustard::NonMoveableBase,
                     public G4Region {
public:
    Region(const G4String& name, RegionType type);

    auto Type() const -> auto { return fRegionType; }

private:
    const RegionType fRegionType;
};

} // namespace MACE::PhaseI::SimMACEPhaseI
