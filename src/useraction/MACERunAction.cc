#include "useraction/MACERunAction.hh"
#include "messenger/MACERunMessenger.hh"
#include "useraction/MACEPrimaryGeneratorAction.hh"
#include "MACEProgressMonitor.hh"
#include "MACEAnalysisManager.hh"

#include "G4Run.hh"
#include "G4MTRunManager.hh"
#include "G4UnitsTable.hh"

MACERunAction::MACERunAction() :
    fMessenger(new MACERunMessenger(this)) {
    MACEProgressMonitor::Instance().SetNumberOfEventsPerReport(100);
}

MACERunAction::~MACERunAction() {
    delete fMessenger;
}

void MACERunAction::BeginOfRunAction(const G4Run*) {
    MACEAnalysisManager::Open();
    MACEProgressMonitor::Instance().RunStart();
}

void MACERunAction::EndOfRunAction(const G4Run*) {
    MACEAnalysisManager::Close();
    MACEProgressMonitor::Instance().RunComplete();
}
