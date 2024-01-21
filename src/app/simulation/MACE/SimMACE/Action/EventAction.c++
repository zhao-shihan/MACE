#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/SimMACE/Action/EventAction.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/CDCSD.h++"
#include "MACE/SimMACE/SD/EMCSD.h++"
#include "MACE/SimMACE/SD/MCPSD.h++"

#include "G4Event.hh"

namespace MACE::SimMACE::inline Action {

auto EventAction::BeginOfEventAction(const G4Event* event) -> void {
    const auto eventID = event->GetEventID();
    const auto& detectors = DetectorConstruction::Instance();
    detectors.EMCSD().EventID(eventID);
    detectors.CDCSD().EventID(eventID);
    detectors.MCPSD().EventID(eventID);
}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance().EventEnd();
}

} // namespace MACE::SimMACE::inline Action
