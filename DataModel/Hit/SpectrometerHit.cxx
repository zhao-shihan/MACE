#include "DataModel/Hit/SpectrometerHit.hxx"

using namespace MACE::DataModel;

Column<Float_t> SpectrometerHit::fgHitTime = { "HitT", 0.0f };
Column<Float_t> SpectrometerHit::fgWirePositionX = { "WireX", 0.0f };
Column<Float_t> SpectrometerHit::fgWirePositionY = { "WireY", 0.0f };
Column<Float_t> SpectrometerHit::fgDriftDistance = { "DriftD",0.0f };
Column<Float_t> SpectrometerHit::fgDriftDistanceVariance = { "DriftDVar",0.0f };
Column<Float_t> SpectrometerHit::fgHitPositionZ = { "HitZ", 0.0f };
Column<Float_t> SpectrometerHit::fgHitPositionZVariance = { "HitZVar", 0.0f };
Column<Int_t> SpectrometerHit::fgCellID = { "CellID", -1 };
Column<Int_t> SpectrometerHit::fgLayerID = { "LayerID", -1 };

SpectrometerHit::SpectrometerHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fWirePosition(fgWirePositionX.value, fgWirePositionY.value),
    fDriftDistance(fgDriftDistance.value),
    fDriftDistanceVariance(fgDriftDistanceVariance.value),
    fHitPositionZ(fgHitPositionZ.value),
    fHitPositionZVariance(fgHitPositionZVariance.value),
    fCellID(fgCellID.value),
    fLayerID(fgLayerID.value) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fWirePosition(hit.fWirePosition),
    fDriftDistance(hit.fDriftDistance),
    fDriftDistanceVariance(hit.fDriftDistanceVariance),
    fHitPositionZ(hit.fHitPositionZ),
    fHitPositionZVariance(hit.fHitPositionZVariance),
    fCellID(hit.fCellID),
    fLayerID(hit.fLayerID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fWirePosition(std::move(hit.fWirePosition)),
    fDriftDistance(std::move(hit.fDriftDistance)),
    fDriftDistanceVariance(std::move(hit.fDriftDistanceVariance)),
    fHitPositionZ(std::move(hit.fHitPositionZ)),
    fHitPositionZVariance(std::move(hit.fHitPositionZVariance)),
    fCellID(std::move(hit.fCellID)),
    fLayerID(std::move(hit.fLayerID)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        Data::operator=(static_cast<const Data&>(hit));
        fHitTime = hit.fHitTime;
        fWirePosition = hit.fWirePosition;
        fDriftDistance = hit.fDriftDistance;
        fDriftDistanceVariance = hit.fDriftDistanceVariance;
        fHitPositionZ = hit.fHitPositionZ;
        fHitPositionZVariance = hit.fHitPositionZVariance;
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
        fDriftDistanceVariance = std::move(hit.fDriftDistanceVariance);
        fHitPositionZ = std::move(hit.fHitPositionZ);
        fHitPositionZVariance = std::move(hit.fHitPositionZVariance);
        fCellID = std::move(hit.fCellID);
        fLayerID = std::move(hit.fLayerID);
    }
    return *this;
}

void SpectrometerHit::CreateBranches(const std::shared_ptr<TTree>& tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgHitTime.name, std::addressof(fgHitTime.value));
    tree->Branch(fgWirePositionX.name, std::addressof(fgWirePositionX.value));
    tree->Branch(fgWirePositionY.name, std::addressof(fgWirePositionY.value));
    tree->Branch(fgDriftDistance.name, std::addressof(fgDriftDistance.value));
    tree->Branch(fgDriftDistanceVariance.name, std::addressof(fgDriftDistanceVariance.value));
    tree->Branch(fgHitPositionZ.name, std::addressof(fgHitPositionZ.value));
    tree->Branch(fgHitPositionZVariance.name, std::addressof(fgHitPositionZVariance.value));
    tree->Branch(fgCellID.name, std::addressof(fgCellID.value));
    tree->Branch(fgLayerID.name, std::addressof(fgLayerID.value));
}

void SpectrometerHit::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgHitTime.name, std::addressof(fgHitTime.value));
    tree->SetBranchAddress(fgWirePositionX.name, std::addressof(fgWirePositionX.value));
    tree->SetBranchAddress(fgWirePositionY.name, std::addressof(fgWirePositionY.value));
    tree->SetBranchAddress(fgDriftDistance.name, std::addressof(fgDriftDistance.value));
    tree->SetBranchAddress(fgDriftDistanceVariance.name, std::addressof(fgDriftDistanceVariance.value));
    tree->SetBranchAddress(fgHitPositionZ.name, std::addressof(fgHitPositionZ.value));
    tree->SetBranchAddress(fgHitPositionZVariance.name, std::addressof(fgHitPositionZVariance.value));
    tree->SetBranchAddress(fgCellID.name, std::addressof(fgCellID.value));
    tree->SetBranchAddress(fgLayerID.name, std::addressof(fgLayerID.value));
}
