#include "DataModel/Hit/SpectrometerHit.hxx"

using namespace MACE::DataModel::Hit;

MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitTime = { "HitT", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgWirePositionX = { "WireX", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgWirePositionY = { "WireY", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgDriftDistance = { "DriftD",0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitPositionZ = { "HitZ", 0.0f };
MACE::DataModel::Column<Int_t> SpectrometerHit::fgCellID = { "CellID", -1 };
MACE::DataModel::Column<Int_t> SpectrometerHit::fgLayerID = { "LayerID", -1 };

SpectrometerHit::SpectrometerHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fWirePosition(fgWirePositionX.value, fgWirePositionY.value),
    fDriftDistance(fgDriftDistance.value),
    fHitPositionZ(fgHitPositionZ.value),
    fCellID(fgCellID.value),
    fLayerID(fgLayerID.value) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fWirePosition(hit.fWirePosition),
    fDriftDistance(hit.fDriftDistance),
    fHitPositionZ(hit.fHitPositionZ),
    fCellID(hit.fCellID),
    fLayerID(hit.fLayerID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fWirePosition(std::move(hit.fWirePosition)),
    fDriftDistance(std::move(hit.fDriftDistance)),
    fHitPositionZ(std::move(hit.fHitPositionZ)),
    fCellID(std::move(hit.fCellID)),
    fLayerID(std::move(hit.fLayerID)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        Data::operator=(static_cast<const Data&>(hit));
        fHitTime = hit.fHitTime;
        fWirePosition = hit.fWirePosition;
        fDriftDistance = hit.fDriftDistance;
        fHitPositionZ = hit.fHitPositionZ;
        fCellID = hit.fCellID;
        fLayerID = hit.fLayerID;
    }
    return *this;
}

SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        Data::operator=(static_cast<Data&&>(hit));
        fHitTime = std::move(hit.fHitTime);
        fWirePosition = std::move(hit.fWirePosition);
        fDriftDistance = std::move(hit.fDriftDistance);
        fHitPositionZ = std::move(hit.fHitPositionZ);
        fCellID = std::move(hit.fCellID);
        fLayerID = std::move(hit.fLayerID);
    }
    return *this;
}

void SpectrometerHit::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgHitTime.name, std::addressof(fgHitTime.value));
    tree->Branch(fgWirePositionX.name, std::addressof(fgWirePositionX.value));
    tree->Branch(fgWirePositionY.name, std::addressof(fgWirePositionY.value));
    tree->Branch(fgDriftDistance.name, std::addressof(fgDriftDistance.value));
    tree->Branch(fgHitPositionZ.name, std::addressof(fgHitPositionZ.value));
    tree->Branch(fgCellID.name, std::addressof(fgCellID.value));
    tree->Branch(fgLayerID.name, std::addressof(fgLayerID.value));
}

void SpectrometerHit::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgHitTime.name, std::addressof(fgHitTime.value));
    tree->SetBranchAddress(fgWirePositionX.name, std::addressof(fgWirePositionX.value));
    tree->SetBranchAddress(fgWirePositionY.name, std::addressof(fgWirePositionY.value));
    tree->SetBranchAddress(fgDriftDistance.name, std::addressof(fgDriftDistance.value));
    tree->SetBranchAddress(fgHitPositionZ.name, std::addressof(fgHitPositionZ.value));
    tree->SetBranchAddress(fgCellID.name, std::addressof(fgCellID.value));
    tree->SetBranchAddress(fgLayerID.name, std::addressof(fgLayerID.value));
}
