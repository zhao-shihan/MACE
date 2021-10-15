#include "DataModel/Hit/SpectrometerHit.hh"

using namespace MACE::DataModel::Hit;

Float_t SpectrometerHit::persistHitTime = 0.0f;
std::array<Float_t, 3> SpectrometerHit::persistHitPosition = { 0.0f, 0.0f, 0.0f };
Int_t SpectrometerHit::persistChamberID = -1;

SpectrometerHit::SpectrometerHit() noexcept :
    Data(),
    fHitTime(0.0),
    fHitPosition(),
    fChamberID(-1) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition),
    fChamberID(hit.fChamberID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)),
    fChamberID(std::move(hit.fChamberID)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    Data::operator=(static_cast<const Data&>(hit));
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    fChamberID = hit.fChamberID;
    return *this;
}

SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
    Data::operator=(static_cast<Data&&>(hit));
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    fChamberID = std::move(hit.fChamberID);
    return *this;
}

void SpectrometerHit::CreateBranches(TTree* tree) {
    tree->Branch("HitT", &persistHitTime);
    tree->Branch("HitX", &std::get<0>(persistHitPosition));
    tree->Branch("HitY", &std::get<1>(persistHitPosition));
    tree->Branch("HitZ", &std::get<2>(persistHitPosition));
    tree->Branch("ChamberID", &persistChamberID);
}

void SpectrometerHit::FillBranches() noexcept {
    persistHitTime = fHitTime;
    std::get<0>(persistHitPosition) = fHitPosition.x();
    std::get<1>(persistHitPosition) = fHitPosition.y();
    std::get<2>(persistHitPosition) = fHitPosition.z();
    persistChamberID = fChamberID;
}