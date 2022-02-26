#include "G4Event.hh"

#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/Action/RunAction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "G4RunManager.hh"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"

#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE::Action;

EventAction::EventAction(ObserverPtr<const RunAction> runAction) :
    fRunAction(runAction) {}

void EventAction::BeginOfEventAction(const G4Event* event) {
    fTrueEventID = fRunAction->GetFirstTrueEventID() + event->GetEventID();
}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance().WriteEvent(static_cast<const PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction())->GetRepetitionID());
}
