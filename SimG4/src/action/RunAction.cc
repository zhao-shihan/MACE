#include <sstream>

#include "g4analysis.hh"
#include "G4MPImanager.hh"

#include "action/RunAction.hh"

using namespace MACE::SimG4;

RunAction::RunAction() :
    G4UserRunAction() {
    auto analysis = G4Analysis::ManagerInstance("root");

    analysis->CreateNtuple("Calorimeter", "Calorimeter");
    analysis->CreateNtupleIColumn("TrackID");
    analysis->CreateNtupleFColumn("HitTime");
    analysis->CreateNtupleFColumn("Energy");
    analysis->FinishNtuple();

    analysis->CreateNtuple("OrbitalDetector", "OrbitalDetector");
    analysis->CreateNtupleIColumn("TrackID");
    analysis->CreateNtupleFColumn("VertexTime");
    analysis->CreateNtupleFColumn("VertexPositionX");
    analysis->CreateNtupleFColumn("VertexPositionY");
    analysis->CreateNtupleFColumn("VertexPositionZ");
    analysis->CreateNtupleFColumn("HitTime");
    analysis->CreateNtupleFColumn("HitPositionX");
    analysis->CreateNtupleFColumn("HitPositionY");
    analysis->CreateNtupleFColumn("HitPositionZ");
    analysis->FinishNtuple();

    analysis->CreateNtuple("Spectrometer", "Spectrometer");
    analysis->CreateNtupleIColumn("TrackID");
    analysis->CreateNtupleIColumn("ChamberID");
    analysis->CreateNtupleFColumn("VertexTime");
    analysis->CreateNtupleFColumn("VertexPositionX");
    analysis->CreateNtupleFColumn("VertexPositionY");
    analysis->CreateNtupleFColumn("VertexPositionZ");
    analysis->CreateNtupleFColumn("HitTime");
    analysis->CreateNtupleFColumn("HitPositionX");
    analysis->CreateNtupleFColumn("HitPositionY");
    analysis->CreateNtupleFColumn("HitPositionZ");
    analysis->FinishNtuple();
}

RunAction::~RunAction() {
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*) {
    G4String fileName = "MACE_SimG4";
    if (MPI::Is_initialized()) {
        std::stringstream ss;
        ss << fileName << "_rank" << G4MPImanager::GetManager()->GetRank();
        ss >> fileName;
    }
    G4AnalysisManager::Instance()->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run*) {
    G4AnalysisManager::Instance()->Write();
    G4AnalysisManager::Instance()->CloseFile();
}
