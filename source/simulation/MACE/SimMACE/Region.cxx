#include "MACE/SimMACE/Region.hxx"

namespace MACE::SimMACE {

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}

} // namespace MACE::SimMACE
