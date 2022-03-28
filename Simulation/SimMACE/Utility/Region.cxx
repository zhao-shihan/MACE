#include "Simulation/SimMACE/Utility/Region.hxx"

using MACE::Simulation::SimMACE::Utility::Region;

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}
