#include "userAction/PSIMACERunAction.hh"
#include "messenger/PSIMACERunMessenger.hh"
#include "userAction/PSIMACEPrimaryGeneratorAction.hh"
#include "PSIMACEAnalysisManager.hh"
#include "PSIMACEProgressMonitor.hh"

#include "G4Run.hh"
#include "G4MTRunManager.hh"
#include "G4UnitsTable.hh"

PSIMACERunAction::PSIMACERunAction() :
    fMessenger(new PSIMACERunMessenger(this)) {
    PSIMACEProgressMonitor::Instance()->SetNumberOfEventsPerReport(100);
}

PSIMACERunAction::~PSIMACERunAction() {
    delete fMessenger;
}

void PSIMACERunAction::BeginOfRunAction(const G4Run*) {
    PSIMACEAnalysisManager::Instance()->Open();
    PSIMACEProgressMonitor::Instance()->RunStart();
}

void PSIMACERunAction::EndOfRunAction(const G4Run*) {
    PSIMACEAnalysisManager::Instance()->Close();
    PSIMACEProgressMonitor::Instance()->RunComplete();
}
