#include "MACE/SimMMS/Region.h++"

namespace MACE::SimMMS {

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}

} // namespace MACE::SimMMS
