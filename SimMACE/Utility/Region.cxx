#include "SimMACE/Utility/Region.hxx"

using namespace MACE::SimMACE::Utility;

Region::Region(const G4String& name, RegionType type) :
    G4Region(name),
    fRegionType(type) {}
