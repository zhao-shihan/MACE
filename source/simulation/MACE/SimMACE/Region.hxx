#pragma once

#include "G4Region.hh"

namespace MACE::SimMACE {

class Region final : public G4Region {
public:
    enum RegionType {
        kEMCalSensitive,
        kDefaultSolid,
        kDefaultGaseous,
        kShield,
        kSolenoidOrMagnet,
        kSpectrometerSensitive,
        kTarget,
        kVacuum,
        kMCPSensitive
    };

public:
    Region(const G4String& name, RegionType type);
    ~Region() noexcept = default;
    Region(const Region&) = delete;
    Region& operator=(const Region&) = delete;

    auto GetType() const { return fRegionType; }

private:
    const RegionType fRegionType;
};

} // namespace MACE::SimMACE
