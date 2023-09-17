#include "MACE/Simulation/SimMACE/Region.h++"

namespace MACE::inline Simulation::SimMACE {

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}

} // namespace MACE::inline Simulation::SimMACE
