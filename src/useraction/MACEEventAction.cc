#include "useraction/MACEEventAction.hh"
#include "MACEAnalysisManager.hh"
#include "MACEProgressMonitor.hh"

#include "G4Event.hh"

MACEEventAction::MACEEventAction() :
    G4UserEventAction() {}

MACEEventAction::~MACEEventAction() {}

void MACEEventAction::BeginOfEventAction(const G4Event*) {}

void MACEEventAction::EndOfEventAction(const G4Event*) {
    MACEAnalysisManager::ThreadLocalInstance().AnalysisAndWrite();
    MACEProgressMonitor::Instance().EventComplete();
}
