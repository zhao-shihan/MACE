#include "userAction/PSIMACEEventAction.hh"
#include "PSIMACEAnalysisManager.hh"
#include "PSIMACEProgressMonitor.hh"

#include "G4Event.hh"

PSIMACEEventAction::PSIMACEEventAction() :
    G4UserEventAction() {}

PSIMACEEventAction::~PSIMACEEventAction() {}

void PSIMACEEventAction::BeginOfEventAction(const G4Event*) {}

void PSIMACEEventAction::EndOfEventAction(const G4Event*) {
    PSIMACEAnalysisManager::ThreadLocalInstance().AnalysisAndWrite();
    PSIMACEProgressMonitor::Instance().EventComplete();
}
