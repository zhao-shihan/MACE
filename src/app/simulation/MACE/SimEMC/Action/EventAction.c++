#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/Action/EventAction.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"

#include "G4Event.hh"

namespace MACE::SimEMC::inline Action {

auto EventAction::BeginOfEventAction(const G4Event* event) -> void {
    const auto eventID = event->GetEventID();
    const auto& detectors = DetectorConstruction::Instance();
    detectors.EMCSD().EventID(eventID);
    detectors.EMCPMTSD().EventID(eventID);
    detectors.MCPSD().EventID(eventID);
}

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    Analysis::Instance().EventEnd();
}

} // namespace MACE::SimEMC::inline Action
