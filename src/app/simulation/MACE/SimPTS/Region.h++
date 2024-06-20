#pragma once

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4Region.hh"

namespace MACE::SimPTS {

enum struct RegionType {
    DefaultGaseous,
    DefaultSolid,
    Shield,
    SolenoidOrMagnet,
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

} // namespace MACE::SimPTS
