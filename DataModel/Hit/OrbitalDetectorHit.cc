#include "DataModel/Hit/OrbitalDetectorHit.hh"

using namespace MACE::DataModel::Hit;

Float_t OrbitalDetectorHit::persistHitTime = 0.0f;
std::array<Float_t, 3> OrbitalDetectorHit::persistHitPosition = { 0.0f, 0.0f, 0.0f };

OrbitalDetectorHit::OrbitalDetectorHit() noexcept :
    Data(),
    fHitTime(0.0),
    fHitPosition() {}

OrbitalDetectorHit::OrbitalDetectorHit(const OrbitalDetectorHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition) {}

OrbitalDetectorHit::OrbitalDetectorHit(OrbitalDetectorHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)) {}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(const OrbitalDetectorHit& hit) noexcept {
    Data::operator=(static_cast<const Data&>(hit));
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    return *this;
}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(OrbitalDetectorHit&& hit) noexcept {
    Data::operator=(static_cast<Data&&>(hit));
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    return *this;
}

void OrbitalDetectorHit::CreateBranches(TTree* tree) {
    tree->Branch("HitT", &persistHitTime);
    tree->Branch("HitX", &std::get<0>(persistHitPosition));
    tree->Branch("HitY", &std::get<1>(persistHitPosition));
    tree->Branch("HitZ", &std::get<2>(persistHitPosition));
}

void OrbitalDetectorHit::FillBranches() noexcept {
    persistHitTime = fHitTime;
    std::get<0>(persistHitPosition) = fHitPosition.x();
    std::get<1>(persistHitPosition) = fHitPosition.y();
    std::get<2>(persistHitPosition) = fHitPosition.z();
}