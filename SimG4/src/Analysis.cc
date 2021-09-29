#include "G4MPImanager.hh"

#include "Analysis.hh"
#include "messenger/AnalysisMessenger.hh"
#include "messenger/FieldMessenger.hh"

using namespace MACE::SimG4;

Analysis* Analysis::instance = nullptr;

Analysis* Analysis::Instance() {
    if (instance == nullptr) {
        instance = new Analysis();
    }
    return instance;
}

Analysis::Analysis() :
    fpG4Analysis(nullptr),
    fpCalorimeterHC(nullptr),
    fpOrbitalDetectorHC(nullptr),
    fpSpectrometerHC(nullptr) {
    AnalysisMessenger::Instance()->Set(this);
}

Analysis::~Analysis() {
    delete fpG4Analysis;
}

void Analysis::Initialize() {
    delete fpG4Analysis;
    fpG4Analysis = G4Analysis::ManagerInstance("root");

    fpG4Analysis->CreateNtuple("Calorimeter", "Calorimeter");
    fpG4Analysis->CreateNtupleIColumn("PluseID");
    fpG4Analysis->CreateNtupleIColumn("TrackID");
    fpG4Analysis->CreateNtupleFColumn("HitTime");
    fpG4Analysis->CreateNtupleFColumn("Energy");
    fpG4Analysis->CreateNtupleSColumn("ParticleName");
    fpG4Analysis->FinishNtuple();

    fpG4Analysis->CreateNtuple("OrbitalDetector", "OrbitalDetector");
    fpG4Analysis->CreateNtupleIColumn("PluseID");
    fpG4Analysis->CreateNtupleIColumn("TrackID");
    fpG4Analysis->CreateNtupleFColumn("VertexTime");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionX");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionY");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionZ");
    fpG4Analysis->CreateNtupleFColumn("HitTime");
    fpG4Analysis->CreateNtupleFColumn("HitPositionX");
    fpG4Analysis->CreateNtupleFColumn("HitPositionY");
    fpG4Analysis->CreateNtupleFColumn("HitPositionZ");
    fpG4Analysis->CreateNtupleSColumn("ParticleName");
    fpG4Analysis->FinishNtuple();

    fpG4Analysis->CreateNtuple("Spectrometer", "Spectrometer");
    fpG4Analysis->CreateNtupleIColumn("PluseID");
    fpG4Analysis->CreateNtupleIColumn("TrackID");
    fpG4Analysis->CreateNtupleIColumn("ChamberID");
    fpG4Analysis->CreateNtupleFColumn("VertexTime");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionX");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionY");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionZ");
    fpG4Analysis->CreateNtupleFColumn("HitTime");
    fpG4Analysis->CreateNtupleFColumn("HitPositionX");
    fpG4Analysis->CreateNtupleFColumn("HitPositionY");
    fpG4Analysis->CreateNtupleFColumn("HitPositionZ");
    fpG4Analysis->CreateNtupleSColumn("ParticleName");
    fpG4Analysis->FinishNtuple();
}

void Analysis::Open() const {
    G4String fullFileName = fFileName;
    if (MPI::Is_initialized()) {
        std::stringstream ss;
        ss << fullFileName << "_rank" << G4MPImanager::GetManager()->GetRank();
        ss >> fullFileName;
    }
    fpG4Analysis->OpenFile(fullFileName);
}

void Analysis::Fill() const {
    if (fEnableCoincidenceOfCalorimeter) {
        if (fpCalorimeterHC->entries() == 0 ||
            fpOrbitalDetectorHC->entries() == 0 ||
            fpSpectrometerHC->entries() == 0) {
            return;
        }
    } else {
        if (fpOrbitalDetectorHC->entries() == 0 ||
            fpSpectrometerHC->entries() == 0) {
            return;
        }
    }

    const auto* const calorimeterHits = fpCalorimeterHC->GetVector();
    for (const auto* const hit : *calorimeterHits) {
        constexpr G4int ntupleID = 0;
        fpG4Analysis->FillNtupleIColumn(ntupleID, 0, fPluseID);
        fpG4Analysis->FillNtupleIColumn(ntupleID, 1, hit->TrackID);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 2, hit->HitTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 3, hit->Energy);
        fpG4Analysis->FillNtupleSColumn(ntupleID, 4, hit->ParticleDefinition->GetParticleName());
        fpG4Analysis->AddNtupleRow(ntupleID);
    }

    const auto* const orbitalDetectorHits = fpOrbitalDetectorHC->GetVector();
    for (const auto* const hit : *orbitalDetectorHits) {
        constexpr G4int ntupleID = 1;
        fpG4Analysis->FillNtupleIColumn(ntupleID, 0, fPluseID);
        fpG4Analysis->FillNtupleIColumn(ntupleID, 1, hit->TrackID);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 2, hit->VertexTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 3, hit->VertexPosition.x());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 4, hit->VertexPosition.y());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 5, hit->VertexPosition.z());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 6, hit->HitTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 7, hit->HitPosition.x());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 8, hit->HitPosition.y());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 9, hit->HitPosition.z());
        fpG4Analysis->FillNtupleSColumn(ntupleID, 10, hit->ParticleDefinition->GetParticleName());
        fpG4Analysis->AddNtupleRow(ntupleID);
    }

    const auto* const spectrometerHits = fpSpectrometerHC->GetVector();
    for (const auto* const hit : *spectrometerHits) {
        constexpr G4int ntupleID = 2;
        fpG4Analysis->FillNtupleIColumn(ntupleID, 0, fPluseID);
        fpG4Analysis->FillNtupleIColumn(ntupleID, 1, hit->TrackID);
        fpG4Analysis->FillNtupleIColumn(ntupleID, 2, hit->ChamberID);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 3, hit->VertexTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 4, hit->VertexPosition.x());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 5, hit->VertexPosition.y());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 6, hit->VertexPosition.z());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 7, hit->HitTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 8, hit->HitPosition.x());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 9, hit->HitPosition.y());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 10, hit->HitPosition.z());
        fpG4Analysis->FillNtupleSColumn(ntupleID, 11, hit->ParticleDefinition->GetParticleName());
        fpG4Analysis->AddNtupleRow(ntupleID);
    }
}

void Analysis::WriteAndClose() const {
    fpG4Analysis->Write();
    fpG4Analysis->CloseFile();
}