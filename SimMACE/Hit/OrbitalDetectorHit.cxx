#include "SimMACE/Hit/OrbitalDetectorHit.hxx"

using namespace MACE::SimMACE::Hit;

MACE::DataModel::Column<Float_t> OrbitalDetectorHit::fgVertexTime = { "VertexT", 0.0f };
MACE::DataModel::Column<Float_t> OrbitalDetectorHit::fgVertexPositionX = { "VertexX", 0.0f };
MACE::DataModel::Column<Float_t> OrbitalDetectorHit::fgVertexPositionY = { "VertexY", 0.0f };
MACE::DataModel::Column<Float_t> OrbitalDetectorHit::fgVertexPositionZ = { "VertexZ", 0.0f };
MACE::DataModel::Column<Int_t> OrbitalDetectorHit::fgPDGCode = { "PDGCode", 0 };
MACE::DataModel::Column<Int_t> OrbitalDetectorHit::fgTrackID = { "TrackID", -1 };

G4Allocator<OrbitalDetectorHit>* MACE::SimMACE::Hit::OrbitalDetectorAllocator = nullptr;

OrbitalDetectorHit::OrbitalDetectorHit() noexcept :
    G4VHit(),
    DataModel::Hit::OrbitalDetectorHit(),
    fVertexTime(fgVertexTime.value),
    fVertexPosition(fgVertexPositionX.value, fgVertexPositionY.value, fgVertexPositionZ.value),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

OrbitalDetectorHit::OrbitalDetectorHit(const OrbitalDetectorHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::Hit::OrbitalDetectorHit(static_cast<const DataModel::Hit::OrbitalDetectorHit&>(hit)),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fPDGCode(hit.fPDGCode),
    fTrackID(hit.fTrackID) {}

OrbitalDetectorHit::OrbitalDetectorHit(OrbitalDetectorHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::Hit::OrbitalDetectorHit(static_cast<DataModel::Hit::OrbitalDetectorHit&&>(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fPDGCode(std::move(hit.fPDGCode)),
    fTrackID(std::move(hit.fTrackID)) {}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(const OrbitalDetectorHit& hit) noexcept {
    if (&hit != this) {
        G4VHit::operator=(static_cast<const G4VHit&>(hit));
        DataModel::Hit::OrbitalDetectorHit::operator=(static_cast<const DataModel::Hit::OrbitalDetectorHit&>(hit));
        fVertexTime = hit.fVertexTime;
        fVertexPosition = hit.fVertexPosition;
        fPDGCode = hit.fPDGCode;
        fTrackID = hit.fTrackID;
    }
    return *this;
}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(OrbitalDetectorHit&& hit) noexcept {
    if (&hit != this) {
        G4VHit::operator=(static_cast<G4VHit&&>(hit));
        DataModel::Hit::OrbitalDetectorHit::operator=(static_cast<DataModel::Hit::OrbitalDetectorHit&&>(hit));
        fVertexTime = std::move(hit.fVertexTime);
        fVertexPosition = std::move(hit.fVertexPosition);
        fPDGCode = std::move(hit.fPDGCode);
        fTrackID = std::move(hit.fTrackID);
    }
    return *this;
}

void OrbitalDetectorHit::CreateBranches(TTree* tree) {
    DataModel::Hit::OrbitalDetectorHit::CreateBranches(tree);
    tree->Branch(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree->Branch(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree->Branch(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree->Branch(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree->Branch(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->Branch(fgTrackID.name, std::addressof(fgTrackID.value));
}

void OrbitalDetectorHit::ReadBranches(TTree* tree) {
    DataModel::Hit::OrbitalDetectorHit::ReadBranches(tree);
    tree->SetBranchAddress(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree->SetBranchAddress(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree->SetBranchAddress(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree->SetBranchAddress(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree->SetBranchAddress(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->SetBranchAddress(fgTrackID.name, std::addressof(fgTrackID.value));
}