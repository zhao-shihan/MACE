#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Action/EventAction.hxx"
#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/SimMACE/SD/EMCalSD.hxx"
#include "MACE/SimMACE/SD/MCPSD.hxx"

#include "G4Event.hh"

namespace MACE::SimMACE::inline Action {

void EventAction::BeginOfEventAction(const G4Event* event) {
    const auto eventID = event->GetEventID();
    const auto& detectors = DetectorConstruction::Instance();
    detectors.GetEMCalSD().SetEventID(eventID);
    detectors.GetCDCSD().SetEventID(eventID);
    detectors.GetMCPSD().SetEventID(eventID);
}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance().EventEnd();
}

} // namespace MACE::SimMACE::inline Action
