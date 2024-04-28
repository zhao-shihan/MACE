#include "MACE/PhaseI/SimMACEPhaseI/Region.h++"

namespace MACE::PhaseI::SimMACEPhaseI {

Region::Region(const G4String& name, RegionType type) :
    G4Region{name},
    fRegionType{type} {}

} // namespace MACE::PhaseI::SimMACEPhaseI
