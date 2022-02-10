#include "DataModel/SimHit/SpectrometerSimHit.hxx"

using namespace MACE::DataModel;

Column<Float_t> SpectrometerSimHit::fgVertexTime = { "VertexT", 0.0f };
Column<Float_t> SpectrometerSimHit::fgVertexPositionX = { "VertexX", 0.0f };
Column<Float_t> SpectrometerSimHit::fgVertexPositionY = { "VertexY", 0.0f };
Column<Float_t> SpectrometerSimHit::fgVertexPositionZ = { "VertexZ", 0.0f };
Column<Int_t> SpectrometerSimHit::fgPDGCode = { "PDGCode", 0 };
Column<Int_t> SpectrometerSimHit::fgTrackID = { "TrackID", -1 };

SpectrometerSimHit::SpectrometerSimHit() noexcept :
    DataModel::SpectrometerHit(),
    fVertexTime(fgVertexTime.value),
    fVertexPosition(fgVertexPositionX.value, fgVertexPositionY.value, fgVertexPositionZ.value),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

SpectrometerSimHit::SpectrometerSimHit(const SpectrometerSimHit& hit) noexcept :
    DataModel::SpectrometerHit(static_cast<const DataModel::SpectrometerHit&>(hit)),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fPDGCode(hit.fPDGCode),
    fTrackID(hit.fTrackID) {}

SpectrometerSimHit::SpectrometerSimHit(SpectrometerSimHit&& hit) noexcept :
    DataModel::SpectrometerHit(static_cast<DataModel::SpectrometerHit&&>(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fPDGCode(std::move(hit.fPDGCode)),
    fTrackID(std::move(hit.fTrackID)) {}

SpectrometerSimHit& SpectrometerSimHit::operator=(const SpectrometerSimHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        DataModel::SpectrometerHit::operator=(static_cast<const DataModel::SpectrometerHit&>(hit));
        fVertexTime = hit.fVertexTime;
        fVertexPosition = hit.fVertexPosition;
        fPDGCode = hit.fPDGCode;
        fTrackID = hit.fTrackID;
    }
    return *this;
}

SpectrometerSimHit& SpectrometerSimHit::operator=(SpectrometerSimHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        DataModel::SpectrometerHit::operator=(static_cast<DataModel::SpectrometerHit&&>(hit));
        fVertexTime = std::move(hit.fVertexTime);
        fVertexPosition = std::move(hit.fVertexPosition);
        fPDGCode = std::move(hit.fPDGCode);
        fTrackID = std::move(hit.fTrackID);
    }
    return *this;
}

void SpectrometerSimHit::CreateBranches(TTree* tree) {
    DataModel::SpectrometerHit::CreateBranches(tree);
    tree->Branch(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree->Branch(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree->Branch(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree->Branch(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree->Branch(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->Branch(fgTrackID.name, std::addressof(fgTrackID.value));
}

void SpectrometerSimHit::ReadBranches(TTree* tree) {
    DataModel::SpectrometerHit::ReadBranches(tree);
    tree->SetBranchAddress(fgVertexTime.name, std::addressof(fgVertexTime.value));
    tree->SetBranchAddress(fgVertexPositionX.name, std::addressof(fgVertexPositionX.value));
    tree->SetBranchAddress(fgVertexPositionY.name, std::addressof(fgVertexPositionY.value));
    tree->SetBranchAddress(fgVertexPositionZ.name, std::addressof(fgVertexPositionZ.value));
    tree->SetBranchAddress(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->SetBranchAddress(fgTrackID.name, std::addressof(fgTrackID.value));
}