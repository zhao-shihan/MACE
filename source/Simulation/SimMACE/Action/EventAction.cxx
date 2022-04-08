#include "Simulation/SimMACE/Action/EventAction.hxx"
#include "Simulation/SimMACE/RunManager.hxx"
#include "Simulation/SimMACE/SD/CDCSD.hxx"
#include "Simulation/SimMACE/SD/EMCalSD.hxx"
#include "Simulation/SimMACE/SD/MCPSD.hxx"
#include "Simulation/SimMACE/Utility/Analysis.hxx"

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
    Utility::Analysis::Instance().WriteEvent(repetitionID);
}

} // namespace MACE::Simulation::SimMACE::Action
