#include "MACE/SimMACE/Action/EventAction.hxx"
#include "MACE/SimMACE/RunManager.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/SimMACE/SD/EMCalSD.hxx"
#include "MACE/SimMACE/SD/MCPSD.hxx"

namespace MACE::SimMACE::Action {

void EventAction::BeginOfEventAction(const G4Event* event) {
    const auto eventID = event->GetEventID();
    const auto& detectors = RunManager::Instance().GetDetectorConstruction();
    detectors.GetEMCalSD().SetEventID(eventID);
    detectors.GetCDCSD().SetEventID(eventID);
    detectors.GetMCPSD().SetEventID(eventID);
}

void EventAction::EndOfEventAction(const G4Event* event) {
    RunManager::Instance().GetAnalysis().WriteEvent(event->GetEventID());
}

} // namespace MACE::SimMACE::Action
