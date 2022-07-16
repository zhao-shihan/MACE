#include "MACE/Simulation/SimMACE/Region.hxx"

namespace MACE::Simulation::SimMACE {

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}

} // namespace MACE::Simulation::SimMACE
