#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/RunManager.hxx"
#include "SimMACE/SD/CalorimeterSD.hxx"
#include "SimMACE/SD/SpectrometerSD.hxx"
#include "SimMACE/SD/VertexDetectorSD.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE::Action;

void EventAction::BeginOfEventAction(const G4Event* event) {
    const auto eventID = event->GetEventID();
    const auto& detectors = RunManager::Instance().GetDetectorConstruction();
    detectors.GetCalorimeterSD().SetEventID(eventID);
    detectors.GetSpectrometerSD().SetEventID(eventID);
    detectors.GetVertexDetectorSD().SetEventID(eventID);
}

void EventAction::EndOfEventAction(const G4Event*) {
    const auto repetitionID = RunManager::Instance().GetPrimaryGeneratorAction().GetRepetitionID();
    Analysis::Instance().WriteEvent(repetitionID);
}
