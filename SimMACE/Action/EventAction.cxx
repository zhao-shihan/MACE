#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/RunManager.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE::Action;

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance().WriteEvent(RunManager::Instance().GetPrimaryGeneratorAction().GetRepetitionID());
}
