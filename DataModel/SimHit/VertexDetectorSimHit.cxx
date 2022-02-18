#include "DataModel/SimHit/VertexDetectorSimHit.hxx"

using namespace MACE::DataModel;

Column<Float_t> VertexDetectorSimHit::fgVertexTime = { "VertexT", 0.0f };
Column<Float_t> VertexDetectorSimHit::fgVertexPositionX = { "VertexX", 0.0f };
Column<Float_t> VertexDetectorSimHit::fgVertexPositionY = { "VertexY", 0.0f };
Column<Float_t> VertexDetectorSimHit::fgVertexPositionZ = { "VertexZ", 0.0f };
Column<Int_t> VertexDetectorSimHit::fgPDGCode = { "PDGCode", 0 };
Column<Int_t> VertexDetectorSimHit::fgTrackID = { "TrackID", -1 };

VertexDetectorSimHit::VertexDetectorSimHit() noexcept :
    VertexDetectorHit(),
    fVertexTime(fgVertexTime.value),
    fVertexPosition(fgVertexPositionX.value, fgVertexPositionY.value, fgVertexPositionZ.value),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

VertexDetectorSimHit::VertexDetectorSimHit(const VertexDetectorSimHit& hit) noexcept :
    VertexDetectorHit(static_cast<const VertexDetectorHit&>(hit)),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fPDGCode(hit.fPDGCode),
    fTrackID(hit.fTrackID) {}

VertexDetectorSimHit::VertexDetectorSimHit(VertexDetectorSimHit&& hit) noexcept :
    VertexDetectorHit(static_cast<VertexDetectorHit&&>(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fPDGCode(std::move(hit.fPDGCode)),
    fTrackID(std::move(hit.fTrackID)) {}

VertexDetectorSimHit& VertexDetectorSimHit::operator=(const VertexDetectorSimHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        VertexDetectorHit::operator=(static_cast<const VertexDetectorHit&>(hit));
        fVertexTime = hit.fVertexTime;
        fVertexPosition = hit.fVertexPosition;
        fPDGCode = hit.fPDGCode;
        fTrackID = hit.fTrackID;
    }
    return *this;
}

VertexDetectorSimHit& VertexDetectorSimHit::operator=(VertexDetectorSimHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        VertexDetectorHit::operator=(static_cast<VertexDetectorHit&&>(hit));
        fVertexTime = std::move(hit.fVertexTime);
        fVertexPosition = std::move(hit.fVertexPosition);
        fPDGCode = std::move(hit.fPDGCode);
        fTrackID = std::move(hit.fTrackID);
    }
    return *this;
}

void VertexDetectorSimHit::CreateBranches(TTree& tree) {
    VertexDetectorHit::CreateBranches(tree);
    tree.Branch(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree.Branch(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree.Branch(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree.Branch(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree.Branch(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree.Branch(fgTrackID.name, std::addressof(fgTrackID.value));
}

void VertexDetectorSimHit::ReadBranches(TTree& tree) {
    VertexDetectorHit::ReadBranches(tree);
    tree.SetBranchAddress(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree.SetBranchAddress(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree.SetBranchAddress(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree.SetBranchAddress(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree.SetBranchAddress(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree.SetBranchAddress(fgTrackID.name, std::addressof(fgTrackID.value));
}