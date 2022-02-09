#include "SimMACE/Hit/VertexDetectorHit.hxx"

using namespace MACE::SimMACE::Hit;

MACE::DataModel::Column<Float_t> VertexDetectorHit::fgVertexTime = { "VertexT", 0.0f };
MACE::DataModel::Column<Float_t> VertexDetectorHit::fgVertexPositionX = { "VertexX", 0.0f };
MACE::DataModel::Column<Float_t> VertexDetectorHit::fgVertexPositionY = { "VertexY", 0.0f };
MACE::DataModel::Column<Float_t> VertexDetectorHit::fgVertexPositionZ = { "VertexZ", 0.0f };
MACE::DataModel::Column<Int_t> VertexDetectorHit::fgPDGCode = { "PDGCode", 0 };
MACE::DataModel::Column<Int_t> VertexDetectorHit::fgTrackID = { "TrackID", -1 };

G4Allocator<VertexDetectorHit>* MACE::SimMACE::Hit::VertexDetectorAllocator = nullptr;

VertexDetectorHit::VertexDetectorHit() noexcept :
    G4VHit(),
    DataModel::Hit::VertexDetectorHit(),
    fVertexTime(fgVertexTime.value),
    fVertexPosition(fgVertexPositionX.value, fgVertexPositionY.value, fgVertexPositionZ.value),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

VertexDetectorHit::VertexDetectorHit(const VertexDetectorHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::Hit::VertexDetectorHit(static_cast<const DataModel::Hit::VertexDetectorHit&>(hit)),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fPDGCode(hit.fPDGCode),
    fTrackID(hit.fTrackID) {}

VertexDetectorHit::VertexDetectorHit(VertexDetectorHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::Hit::VertexDetectorHit(static_cast<DataModel::Hit::VertexDetectorHit&&>(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fPDGCode(std::move(hit.fPDGCode)),
    fTrackID(std::move(hit.fTrackID)) {}

VertexDetectorHit& VertexDetectorHit::operator=(const VertexDetectorHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<const G4VHit&>(hit));
        DataModel::Hit::VertexDetectorHit::operator=(static_cast<const DataModel::Hit::VertexDetectorHit&>(hit));
        fVertexTime = hit.fVertexTime;
        fVertexPosition = hit.fVertexPosition;
        fPDGCode = hit.fPDGCode;
        fTrackID = hit.fTrackID;
    }
    return *this;
}

VertexDetectorHit& VertexDetectorHit::operator=(VertexDetectorHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<G4VHit&&>(hit));
        DataModel::Hit::VertexDetectorHit::operator=(static_cast<DataModel::Hit::VertexDetectorHit&&>(hit));
        fVertexTime = std::move(hit.fVertexTime);
        fVertexPosition = std::move(hit.fVertexPosition);
        fPDGCode = std::move(hit.fPDGCode);
        fTrackID = std::move(hit.fTrackID);
    }
    return *this;
}

void VertexDetectorHit::CreateBranches(TTree* tree) {
    DataModel::Hit::VertexDetectorHit::CreateBranches(tree);
    tree->Branch(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree->Branch(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree->Branch(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree->Branch(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree->Branch(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->Branch(fgTrackID.name, std::addressof(fgTrackID.value));
}

void VertexDetectorHit::ReadBranches(TTree* tree) {
    DataModel::Hit::VertexDetectorHit::ReadBranches(tree);
    tree->SetBranchAddress(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree->SetBranchAddress(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree->SetBranchAddress(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree->SetBranchAddress(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree->SetBranchAddress(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->SetBranchAddress(fgTrackID.name, std::addressof(fgTrackID.value));
}