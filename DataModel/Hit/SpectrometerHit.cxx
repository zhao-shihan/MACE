#include "DataModel/Hit/SpectrometerHit.hxx"

using namespace MACE::DataModel::Hit;

MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitTime = { "HitT", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgWirePositionX = { "WireX", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgWirePositionY = { "WireY", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgDriftDistance = { "DriftD",0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitPositionZ = { "HitZ", 0.0f };
MACE::DataModel::Column<Int_t> SpectrometerHit::fgCellID = { "CellID", -1 };

SpectrometerHit::SpectrometerHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fWirePosition(fgWirePositionX.value, fgWirePositionY.value),
    fDriftDistance(fgDriftDistance.value),
    fHitPositionZ(fgHitPositionZ.value),
    fCellID(fgCellID.value) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fWirePosition(hit.fWirePosition),
    fDriftDistance(hit.fDriftDistance),
    fHitPositionZ(hit.fHitPositionZ),
    fCellID(hit.fCellID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fWirePosition(std::move(hit.fWirePosition)),
    fDriftDistance(std::move(hit.fDriftDistance)),
    fHitPositionZ(std::move(hit.fHitPositionZ)),
    fCellID(std::move(hit.fCellID)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    if (&hit != this) {
        Data::operator=(static_cast<const Data&>(hit));
        fHitTime = hit.fHitTime;
        fWirePosition = hit.fWirePosition;
        fDriftDistance = hit.fDriftDistance;
        fHitPositionZ = hit.fHitPositionZ;
        fCellID = hit.fCellID;
    }
    return *this;
}

SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
    if (&hit != this) {
        Data::operator=(static_cast<Data&&>(hit));
        fHitTime = std::move(hit.fHitTime);
        fWirePosition = std::move(hit.fWirePosition);
        fDriftDistance = std::move(hit.fDriftDistance);
        fHitPositionZ = std::move(hit.fHitPositionZ);
        fCellID = std::move(hit.fCellID);
    }
    return *this;
}

void SpectrometerHit::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgHitTime.name, &fgHitTime.value);
    tree->Branch(fgWirePositionX.name, &fgWirePositionX.value);
    tree->Branch(fgWirePositionY.name, &fgWirePositionY.value);
    tree->Branch(fgDriftDistance.name, &fgDriftDistance.value);
    tree->Branch(fgHitPositionZ.name, &fgHitPositionZ.value);
    tree->Branch(fgCellID.name, &fgCellID.value);
}

void SpectrometerHit::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgHitTime.name, &fgHitTime.value);
    tree->SetBranchAddress(fgWirePositionX.name, &fgWirePositionX.value);
    tree->SetBranchAddress(fgWirePositionY.name, &fgWirePositionY.value);
    tree->SetBranchAddress(fgDriftDistance.name, &fgDriftDistance.value);
    tree->SetBranchAddress(fgHitPositionZ.name, &fgHitPositionZ.value);
    tree->SetBranchAddress(fgCellID.name, &fgCellID.value);
}
