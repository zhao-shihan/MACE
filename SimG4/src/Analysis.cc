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
    FieldMessenger::Instance()->Set(this);
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

template<typename Hit_t>
static inline bool CompareHit(const Hit_t* const hit1, const Hit_t* const hit2) {
    return hit1->HitTime < hit2->HitTime;
}

void Analysis::DoCoincidenceAnalysisAndFill() const {
    std::sort(fpCalorimeterHC->GetVector()->begin(), fpCalorimeterHC->GetVector()->end(), CompareHit<Hit::CalorimeterHit>);
    std::sort(fpOrbitalDetectorHC->GetVector()->begin(), fpOrbitalDetectorHC->GetVector()->end(), CompareHit<Hit::OrbitalDetectorHit>);
    std::sort(fpSpectrometerHC->GetVector()->begin(), fpSpectrometerHC->GetVector()->end(), CompareHit<Hit::SpectrometerHit>);

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

void Analysis::SetFlightDistance(G4double val) {
    fFlightDistance = val;
    fMeanTOF = fFlightDistance / (c_light * sqrt(2 * fEkin / G4Positron::Definition()->GetPDGMass()));
}

void Analysis::SetEkinOfOrbital(G4double val) {
    fEkin = val;
    fMeanTOF = fFlightDistance / (c_light * sqrt(2 * fEkin / G4Positron::Definition()->GetPDGMass()));
}

void Analysis::FillOrbitalDetectorHit(const Hit::OrbitalDetectorHit* const hit) const {
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

void Analysis::FillCalorimeterHits(std::vector<Hit::CalorimeterHit*>::const_iterator& hitBegin, const std::vector<Hit::CalorimeterHit*>::const_iterator hitEnd) const {
    constexpr G4int ntupleID = 0;
    for (; hitBegin != hitEnd; ++hitBegin) {
        const auto* const hit = *hitBegin;
        fpG4Analysis->FillNtupleIColumn(ntupleID, 0, fPluseID);
        fpG4Analysis->FillNtupleIColumn(ntupleID, 1, hit->TrackID);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 2, hit->HitTime);
        fpG4Analysis->FillNtupleFColumn(ntupleID, 3, hit->Energy);
        fpG4Analysis->FillNtupleSColumn(ntupleID, 4, hit->ParticleDefinition->GetParticleName());
        fpG4Analysis->AddNtupleRow(ntupleID);
    }
}

void Analysis::FillSpectrometerHits(std::vector<Hit::SpectrometerHit*>::const_iterator& hitBegin, const std::vector<Hit::SpectrometerHit*>::const_iterator hitEnd) const {
    constexpr G4int ntupleID = 2;
    for (; hitBegin != hitEnd; ++hitBegin) {
        const auto* const hit = *hitBegin;
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