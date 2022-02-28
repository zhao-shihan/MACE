#pragma once

#include "G4Region.hh"

#include "MACEGlobal.hxx"

namespace MACE::SimMACE::Utility {
    enum RegionType {
        kCalorimeterSensitiveRegion,
        kDefaultSolidRegion,
        kDefaultGaseousRegion,
        kShieldRegion,
        kSolenoidOrMagnetRegion,
        kSpectrometerSensitiveRegion,
        kTargetRegion,
        kVacuumRegion,
        kVertexDetectorSensitiveRegion
    };
}

class MACE::SimMACE::Region final :
    public G4Region {
public:
    Region(const G4String& name, RegionType type);
    ~Region() noexcept = default;
    Region(const Region&) = delete;
    Region& operator=(const Region&) = delete;

    auto GetType() const { return fRegionType; }

private:
    const RegionType fRegionType;
};
