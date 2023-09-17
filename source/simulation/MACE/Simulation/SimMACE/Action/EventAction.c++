#include "MACE/Simulation/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/Simulation/SimMACE/Action/EventAction.h++"
#include "MACE/Simulation/SimMACE/Analysis.h++"
#include "MACE/Simulation/SimMACE/SD/CDCSD.h++"
#include "MACE/Simulation/SimMACE/SD/EMCSD.h++"
#include "MACE/Simulation/SimMACE/SD/MCPSD.h++"

#include "G4Event.hh"

namespace MACE::inline Simulation::SimMACE::inline Action {

void EventAction::BeginOfEventAction(const G4Event* event) {
    const auto eventID = event->GetEventID();
    const auto& detectors = DetectorConstruction::Instance();
    detectors.EMCSD().EventID(eventID);
    detectors.CDCSD().EventID(eventID);
    detectors.MCPSD().EventID(eventID);
}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance().EventEnd();
}

} // namespace MACE::inline Simulation::SimMACE::inline Action
