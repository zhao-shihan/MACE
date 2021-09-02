#include "Analysis.hh"

using namespace MACE::SimG4;

Analysis* Analysis::instance = nullptr;

Analysis* Analysis::Instance() {
    if (instance == nullptr) {
        instance = new Analysis();
    }
    return instance;
}

Analysis::Analysis() :
    fpAnalysis(nullptr),
    fpCalorimeterHC(nullptr),
    fpOrbitalDetectorHC(nullptr),
    fpSpectrometerHC(nullptr) {}

Analysis::~Analysis() {
    delete fpAnalysis;
}

void Analysis::Initialize() {
    delete fpAnalysis;
    fpAnalysis = G4Analysis::ManagerInstance("root");

    fpAnalysis->CreateNtuple("Calorimeter", "Calorimeter");
    fpAnalysis->CreateNtupleIColumn("TrackID");
    fpAnalysis->CreateNtupleFColumn("HitTime");
    fpAnalysis->CreateNtupleFColumn("Energy");
    fpAnalysis->FinishNtuple();

    fpAnalysis->CreateNtuple("OrbitalDetector", "OrbitalDetector");
    fpAnalysis->CreateNtupleIColumn("TrackID");
    fpAnalysis->CreateNtupleFColumn("VertexTime");
    fpAnalysis->CreateNtupleFColumn("VertexPositionX");
    fpAnalysis->CreateNtupleFColumn("VertexPositionY");
    fpAnalysis->CreateNtupleFColumn("VertexPositionZ");
    fpAnalysis->CreateNtupleFColumn("HitTime");
    fpAnalysis->CreateNtupleFColumn("HitPositionX");
    fpAnalysis->CreateNtupleFColumn("HitPositionY");
    fpAnalysis->CreateNtupleFColumn("HitPositionZ");
    fpAnalysis->FinishNtuple();

    fpAnalysis->CreateNtuple("Spectrometer", "Spectrometer");
    fpAnalysis->CreateNtupleIColumn("TrackID");
    fpAnalysis->CreateNtupleIColumn("ChamberID");
    fpAnalysis->CreateNtupleFColumn("VertexTime");
    fpAnalysis->CreateNtupleFColumn("VertexPositionX");
    fpAnalysis->CreateNtupleFColumn("VertexPositionY");
    fpAnalysis->CreateNtupleFColumn("VertexPositionZ");
    fpAnalysis->CreateNtupleFColumn("HitTime");
    fpAnalysis->CreateNtupleFColumn("HitPositionX");
    fpAnalysis->CreateNtupleFColumn("HitPositionY");
    fpAnalysis->CreateNtupleFColumn("HitPositionZ");
    fpAnalysis->FinishNtuple();
}

void Analysis::Open(const G4String& fileName) const {
    fpAnalysis->OpenFile(fileName);
}

void Analysis::DoCoincidenceAnalysisAndFill() const {
    const auto* const calorimeterHits = fpCalorimeterHC->GetVector();
    const auto* const orbitalDetectorHits = fpOrbitalDetectorHC->GetVector();
    const auto* const spectrometerHits = fpSpectrometerHC->GetVector();

    const G4double calorimeterWindowWidth = 2 * ns;
    const G4double meanTOF = 2985 * mm / (c_light * sqrt(2 * 2 * keV / (511 * keV)));
    const G4double spectrometerWindowWidth = 8 * ns;

    auto calorimeterHitBegin = calorimeterHits->begin();
    auto calorimeterHitEnd = calorimeterHitBegin;
    auto spectrometerHitBegin = spectrometerHits->begin();
    auto spectrometerHitEnd = spectrometerHitBegin;

    for (const auto* const orbitalDetectorHit : *orbitalDetectorHits) {
        const G4double calorimeterWindowBegin = orbitalDetectorHit->HitTime;
        const G4double calorimeterWindowEnd = calorimeterWindowBegin + calorimeterWindowWidth;
        while (calorimeterHitBegin != calorimeterHits->end()) {
            if ((*calorimeterHitBegin)->HitTime < calorimeterWindowBegin) { ++calorimeterHitBegin; } else { break; }
        }
        while (calorimeterHitEnd != calorimeterHits->end()) {
            if ((*calorimeterHitEnd)->HitTime < calorimeterWindowEnd) { ++calorimeterHitEnd; } else { break; }
        }

        const G4double spectrometerWindowBegin = orbitalDetectorHit->HitTime - meanTOF - 0.5 * spectrometerWindowWidth;
        const G4double spectrometerWindowEnd = spectrometerWindowBegin + spectrometerWindowWidth;
        while (spectrometerHitBegin != spectrometerHits->end()) {
            if ((*spectrometerHitBegin)->HitTime < spectrometerWindowBegin) { ++spectrometerHitBegin; } else { break; }
        }
        while (spectrometerHitEnd != spectrometerHits->end()) {
            if ((*spectrometerHitEnd)->HitTime < spectrometerWindowEnd) { ++spectrometerHitEnd; } else { break; }
        }

        if (spectrometerHitBegin != spectrometerHitEnd && calorimeterHitBegin != calorimeterHitEnd) {
            FillOrbitalDetectorHit(orbitalDetectorHit);
            FillCalorimeterHits(calorimeterHitBegin, calorimeterHitEnd);
            FillSpectrometerHits(spectrometerHitBegin, spectrometerHitEnd);
        }
    }
}

void Analysis::WriteAndClose() const {
    fpAnalysis->Write();
    fpAnalysis->CloseFile();
}

void Analysis::FillOrbitalDetectorHit(const Hit::OrbitalDetectorHit* const hit) const {
    constexpr G4int ntupleID = 1;
    fpAnalysis->FillNtupleIColumn(ntupleID, 0, hit->TrackID);
    fpAnalysis->FillNtupleFColumn(ntupleID, 1, hit->VertexTime);
    fpAnalysis->FillNtupleFColumn(ntupleID, 2, hit->VertexPosition.x());
    fpAnalysis->FillNtupleFColumn(ntupleID, 3, hit->VertexPosition.y());
    fpAnalysis->FillNtupleFColumn(ntupleID, 4, hit->VertexPosition.z());
    fpAnalysis->FillNtupleFColumn(ntupleID, 5, hit->HitTime);
    fpAnalysis->FillNtupleFColumn(ntupleID, 6, hit->HitPosition.x());
    fpAnalysis->FillNtupleFColumn(ntupleID, 7, hit->HitPosition.y());
    fpAnalysis->FillNtupleFColumn(ntupleID, 8, hit->HitPosition.z());
    fpAnalysis->AddNtupleRow(ntupleID);
}

void Analysis::FillCalorimeterHits(const std::vector<Hit::CalorimeterHit*>::const_iterator hitBegin, const std::vector<Hit::CalorimeterHit*>::const_iterator hitEnd) const {
    constexpr G4int ntupleID = 0;
    for (auto hitIter = hitBegin; hitIter != hitEnd; ++hitIter) {
        const auto* const hit = *hitIter;
        fpAnalysis->FillNtupleIColumn(ntupleID, 0, hit->TrackID);
        fpAnalysis->FillNtupleFColumn(ntupleID, 1, hit->HitTime);
        fpAnalysis->FillNtupleFColumn(ntupleID, 2, hit->Energy);
        fpAnalysis->AddNtupleRow(ntupleID);
    }
}

void Analysis::FillSpectrometerHits(const std::vector<Hit::SpectrometerHit*>::const_iterator hitBegin, const std::vector<Hit::SpectrometerHit*>::const_iterator hitEnd) const {
    constexpr G4int ntupleID = 2;
    for (auto hitIter = hitBegin; hitIter != hitEnd; ++hitIter) {
        const auto* const hit = *hitIter;
        fpAnalysis->FillNtupleIColumn(ntupleID, 0, hit->TrackID);
        fpAnalysis->FillNtupleIColumn(ntupleID, 1, hit->ChamberID);
        fpAnalysis->FillNtupleFColumn(ntupleID, 2, hit->VertexTime);
        fpAnalysis->FillNtupleFColumn(ntupleID, 3, hit->VertexPosition.x());
        fpAnalysis->FillNtupleFColumn(ntupleID, 4, hit->VertexPosition.y());
        fpAnalysis->FillNtupleFColumn(ntupleID, 5, hit->VertexPosition.z());
        fpAnalysis->FillNtupleFColumn(ntupleID, 6, hit->HitTime);
        fpAnalysis->FillNtupleFColumn(ntupleID, 7, hit->HitPosition.x());
        fpAnalysis->FillNtupleFColumn(ntupleID, 8, hit->HitPosition.y());
        fpAnalysis->FillNtupleFColumn(ntupleID, 9, hit->HitPosition.z());
        fpAnalysis->AddNtupleRow(ntupleID);
    }
}