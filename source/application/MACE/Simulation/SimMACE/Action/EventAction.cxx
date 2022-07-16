#include "MACE/Simulation/SimMACE/Action/EventAction.hxx"
#include "MACE/Simulation/SimMACE/Analysis.hxx"
#include "MACE/Simulation/SimMACE/RunManager.hxx"
#include "MACE/Simulation/SimMACE/SD/CDCSD.hxx"
#include "MACE/Simulation/SimMACE/SD/EMCalSD.hxx"
#include "MACE/Simulation/SimMACE/SD/MCPSD.hxx"

namespace MACE::Simulation::SimMACE::Action {

void EventAction::BeginOfEventAction(const G4Event* event) {
    const auto eventID = event->GetEventID();
    const auto& detectors = RunManager::Instance().GetDetectorConstruction();
    detectors.GetEMCalSD().SetEventID(eventID);
    detectors.GetCDCSD().SetEventID(eventID);
    detectors.GetMCPSD().SetEventID(eventID);
}

void EventAction::EndOfEventAction(const G4Event*) {
    const auto repetitionID = RunManager::Instance().GetPrimaryGeneratorAction().GetRepetitionID();
    Analysis::Instance().WriteEvent(repetitionID);
}

} // namespace MACE::Simulation::SimMACE::Action
