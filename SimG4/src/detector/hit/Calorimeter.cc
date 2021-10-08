#include "detector/hit/Calorimeter.hh"

using namespace MACE::SimG4::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(Calorimeter, ParticleName, "");
MACE_DATA_MODEL_PERSISTIFIER_DEF(Calorimeter, TrackID, -1);

G4Allocator<Calorimeter>* MACE::SimG4::Hit::AllocatorOfCalorimeter = nullptr;

Calorimeter::Calorimeter() noexcept :
    G4VHit(),
    DataModel::Hit::Calorimeter(),
    fParticleName(nullptr),
    fTrackID(-1) {}

Calorimeter::Calorimeter(const Calorimeter& hit) noexcept :
    G4VHit(hit),
    DataModel::Hit::Calorimeter(hit),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

Calorimeter::Calorimeter(Calorimeter&& hit) noexcept :
    G4VHit(std::move(hit)),
    DataModel::Hit::Calorimeter(std::move(hit)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

Calorimeter& Calorimeter::operator=(const Calorimeter& hit) noexcept {
    G4VHit::operator=(hit);
    DataModel::Hit::Calorimeter::operator=(hit);
    fParticleName = hit.fParticleName;
    fTrackID = hit.fTrackID;
    return *this;
}

Calorimeter& Calorimeter::operator=(Calorimeter&& hit) noexcept {
    G4VHit::operator=(std::move(hit));
    DataModel::Hit::Calorimeter::operator=(std::move(hit));
    fParticleName = std::move(hit.fParticleName);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void Calorimeter::CreateBranches(TTree* tree) {
    DataModel::Hit::Calorimeter::CreateBranches(tree);
    tree->Branch("ParticleName", const_cast<char*>(persistParticleName.Data()), "ParticleName/C");
    tree->Branch("TrackID", &persistTrackID);
}

void Calorimeter::FillBranches() {
    DataModel::Hit::Calorimeter::FillBranches();
    persistParticleName = fParticleName;
    persistTrackID = fTrackID;
}