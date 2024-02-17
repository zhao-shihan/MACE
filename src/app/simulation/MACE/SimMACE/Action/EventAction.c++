#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/SimMACE/Action/EventAction.h++"
#include "MACE/SimMACE/Data/Analysis.h++"
#include "MACE/SimMACE/SD/CDCSD.h++"
#include "MACE/SimMACE/SD/EMCSD.h++"
#include "MACE/SimMACE/SD/MCPSD.h++"

#include "G4Event.hh"

namespace MACE::SimMACE::inline Action {

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    Analysis::Instance().EventEnd();
}

} // namespace MACE::SimMACE::inline Action
