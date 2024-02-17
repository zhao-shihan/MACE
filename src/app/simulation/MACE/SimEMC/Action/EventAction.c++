#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/Action/EventAction.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"

#include "G4Event.hh"

namespace MACE::SimEMC::inline Action {

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    Analysis::Instance().EventEnd();
}

} // namespace MACE::SimEMC::inline Action
