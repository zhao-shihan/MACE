#include "G4MPImanager.hh"

#include "Analysis.hh"
#include "messenger/AnalysisMessenger.hh"

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
    AnalysisMessenger::Instance()->SetAnalysis(this);
}

Analysis::~Analysis() {
    delete fpG4Analysis;
}

void Analysis::Initialize() {
    delete fpG4Analysis;
    fpG4Analysis = G4Analysis::ManagerInstance("root");

    fpG4Analysis->CreateNtuple("Calorimeter", "Calorimeter");
    fpG4Analysis->CreateNtupleIColumn("TrackID");
    fpG4Analysis->CreateNtupleFColumn("HitTime");
    fpG4Analysis->CreateNtupleFColumn("Energy");
    fpG4Analysis->FinishNtuple();

    fpG4Analysis->CreateNtuple("OrbitalDetector", "OrbitalDetector");
    fpG4Analysis->CreateNtupleIColumn("TrackID");
    fpG4Analysis->CreateNtupleFColumn("VertexTime");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionX");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionY");
    fpG4Analysis->CreateNtupleFColumn("VertexPositionZ");
    fpG4Analysis->CreateNtupleFColumn("HitTime");
    fpG4Analysis->CreateNtupleFColumn("HitPositionX");
    fpG4Analysis->CreateNtupleFColumn("HitPositionY");
    fpG4Analysis->CreateNtupleFColumn("HitPositionZ");
    fpG4Analysis->FinishNtuple();

    fpG4Analysis->CreateNtuple("Spectrometer", "Spectrometer");
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

void Analysis::DoCoincidenceAnalysisAndFill() const {
    const auto* const calorimeterHits = fpCalorimeterHC->GetVector();
    const auto* const orbitalDetectorHits = fpOrbitalDetectorHC->GetVector();
    const auto* const spectrometerHits = fpSpectrometerHC->GetVector();

    auto calorimeterHitBegin = calorimeterHits->begin();
    auto calorimeterHitEnd = calorimeterHitBegin;
    auto spectrometerHitBegin = spectrometerHits->begin();
    auto spectrometerHitEnd = spectrometerHitBegin;

    for (const auto* const orbitalDetectorHit : *orbitalDetectorHits) {
        const G4double calorimeterWindowBegin = orbitalDetectorHit->HitTime;
        const G4double calorimeterWindowEnd = calorimeterWindowBegin + fCalorimeterWindowWidth;
        while (calorimeterHitBegin != calorimeterHits->end()) {
            if ((*calorimeterHitBegin)->HitTime < calorimeterWindowBegin) { ++calorimeterHitBegin; } else { break; }
        }
        while (calorimeterHitEnd != calorimeterHits->end()) {
            if ((*calorimeterHitEnd)->HitTime < calorimeterWindowEnd) { ++calorimeterHitEnd; } else { break; }
        }

        const G4double spectrometerWindowBegin = orbitalDetectorHit->HitTime - fMeanTOF - 0.5 * fSpectrometerWindowWidth;
        const G4double spectrometerWindowEnd = spectrometerWindowBegin + fSpectrometerWindowWidth;
        while (spectrometerHitBegin != spectrometerHits->end()) {
            if ((*spectrometerHitBegin)->HitTime < spectrometerWindowBegin) { ++spectrometerHitBegin; } else { break; }
        }
        while (spectrometerHitEnd != spectrometerHits->end()) {
            if ((*spectrometerHitEnd)->HitTime < spectrometerWindowEnd) { ++spectrometerHitEnd; } else { break; }
        }

        const G4bool calorimeterCoincidence = (!fEnableCoincidenceOfCalorimeter) || (calorimeterHitBegin != calorimeterHitEnd);
        const G4bool spectrometerCoincidence = (spectrometerHitBegin != spectrometerHitEnd);
        if (calorimeterCoincidence && spectrometerCoincidence) {
            FillOrbitalDetectorHit(orbitalDetectorHit);
            FillCalorimeterHits(calorimeterHitBegin, calorimeterHitEnd);
            FillSpectrometerHits(spectrometerHitBegin, spectrometerHitEnd);
        }
    }
}

void Analysis::WriteAndClose() const {
    fpG4Analysis->Write();
    fpG4Analysis->CloseFile();
}

void Analysis::FillOrbitalDetectorHit(const Hit::OrbitalDetectorHit* const hit) const {
    constexpr G4int ntupleID = 1;
    fpG4Analysis->FillNtupleIColumn(ntupleID, 0, hit->TrackID);
    fpG4Analysis->FillNtupleFColumn(ntupleID, 1, hit->VertexTime);
    fpG4Analysis->FillNtupleFColumn(ntupleID, 2, hit->VertexPosition.x());
    fpG4Analysis->FillNtupleFColumn(ntupleID, 3, hit->VertexPosition.y());
    fpG4Analysis->FillNtupleFColumn(ntupleID, 4, hit->VertexPosition.z());
    fpG4Analysis->FillNtupleFColumn(ntupleID, 5, hit->HitTime);
    fpG4Analysis->FillNtupleFColumn(ntupleID, 6, hit->HitPosition.x());
    fpG4Analysis->FillNtupleFColumn(ntupleID, 7, hit->HitPosition.y());
    fpG4Analysis->FillNtupleFColumn(ntupleID, 8, hit->HitPosition.z());
    fpG4Analysis->AddNtupleRow(ntupleID);
}

void Analysis::FillCalorimeterHits(const std::vector<Hit::CalorimeterHit*>::const_iterator hitBegin, const std::vector<Hit::CalorimeterHit*>::const_iterator hitEnd) const {
    constexpr G4int ntupleID = 0;
    for (auto hitIter = hitBegin; hitIter != hitEnd; ++hitIter) {
        const auto* const hit = *hitIter;
        fpG4Analysis->FillNtupleIColumn(ntupleID, 0, hit->TrackID);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 1, hit->HitTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 2, hit->Energy);
        fpG4Analysis->AddNtupleRow(ntupleID);
    }
}

void Analysis::FillSpectrometerHits(const std::vector<Hit::SpectrometerHit*>::const_iterator hitBegin, const std::vector<Hit::SpectrometerHit*>::const_iterator hitEnd) const {
    constexpr G4int ntupleID = 2;
    for (auto hitIter = hitBegin; hitIter != hitEnd; ++hitIter) {
        const auto* const hit = *hitIter;
        fpG4Analysis->FillNtupleIColumn(ntupleID, 0, hit->TrackID);
        fpG4Analysis->FillNtupleIColumn(ntupleID, 1, hit->ChamberID);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 2, hit->VertexTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 3, hit->VertexPosition.x());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 4, hit->VertexPosition.y());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 5, hit->VertexPosition.z());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 6, hit->HitTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 7, hit->HitPosition.x());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 8, hit->HitPosition.y());
        fpG4Analysis->FillNtupleFColumn(ntupleID, 9, hit->HitPosition.z());
        fpG4Analysis->AddNtupleRow(ntupleID);
    }
}