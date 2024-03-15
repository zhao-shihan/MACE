#include "MACE/SimEMC/Region.h++"

namespace MACE::SimEMC {

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}

} // namespace MACE::SimEMC
