#include "MACE/SimPTS/Region.h++"

namespace MACE::SimPTS {

Region::Region(const G4String& name, RegionType type) :
    G4Region{name},
    fRegionType{type} {}

} // namespace MACE::SimPTS
