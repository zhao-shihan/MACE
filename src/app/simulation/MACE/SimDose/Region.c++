#include "MACE/SimDose/Region.h++"

namespace MACE::SimDose {

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}

} // namespace MACE::SimDose
