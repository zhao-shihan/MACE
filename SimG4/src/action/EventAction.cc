#include "action/EventAction.hh"
#include "Analysis.hh"

using namespace MACE::SimG4;

EventAction::EventAction() :
    G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance()->DoCoincidenceAnalysisAndFill();
}
