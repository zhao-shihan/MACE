#include "MACE/SimMACE/Region.h++"

namespace MACE::SimMACE {

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}

} // namespace MACE::SimMACE
