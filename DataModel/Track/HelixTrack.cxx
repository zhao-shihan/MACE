#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel::Track;

MACE::DataModel::Column<Float_t> HelixTrack::fgCenterX = { "Xc", 0.0f };
MACE::DataModel::Column<Float_t> HelixTrack::fgCenterY = { "Yc", 0.0f };
MACE::DataModel::Column<Float_t> HelixTrack::fgRadius = { "R", 0.0f };
MACE::DataModel::Column<Float_t> HelixTrack::fgZ0 = { "Z0", 0.0f };
MACE::DataModel::Column<Float_t> HelixTrack::fgAlpha = { "Alpha", 0.0f };

HelixTrack::HelixTrack() noexcept :
    Data(),
    fCenter(fgCenterX.value, fgCenterY.value),
    fRadius(fgRadius.value),
    fZ0(fgZ0.value),
    fAlpha(fgAlpha.value) {}

HelixTrack::HelixTrack(const HelixTrack& track) noexcept :
    Data(static_cast<const Data&>(track)),
    fCenter(track.fCenter),
    fRadius(track.fRadius),
    fZ0(track.fZ0),
    fAlpha(track.fAlpha) {}

HelixTrack::HelixTrack(HelixTrack&& track) noexcept :
    Data(static_cast<Data&&>(track)),
    fCenter(std::move(track.fCenter)),
    fRadius(std::move(track.fRadius)),
    fZ0(std::move(track.fZ0)),
    fAlpha(std::move(track.fAlpha)) {}

HelixTrack& HelixTrack::operator=(const HelixTrack& track) noexcept {
    if (std::addressof(track) != this) {
        Data::operator=(static_cast<const Data&>(track));
        fCenter = track.fCenter;
        fRadius = track.fRadius;
        fZ0 = track.fZ0;
        fAlpha = track.fAlpha;
    }
    return *this;
}

HelixTrack& HelixTrack::operator=(HelixTrack&& track) noexcept {
    if (std::addressof(track) != this) {
        Data::operator=(static_cast<Data&&>(track));
        fCenter = std::move(track.fCenter);
        fRadius = std::move(track.fRadius);
        fZ0 = std::move(track.fZ0);
        fAlpha = std::move(track.fAlpha);
    }
    return *this;
}

void HelixTrack::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgCenterX.name, std::addressof(fgCenterX.value));
    tree->Branch(fgCenterY.name, std::addressof(fgCenterY.value));
    tree->Branch(fgRadius.name, std::addressof(fgRadius.value));
    tree->Branch(fgZ0.name, std::addressof(fgZ0.value));
    tree->Branch(fgAlpha.name, std::addressof(fgAlpha.value));
}

void HelixTrack::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgCenterX.name, std::addressof(fgCenterX.value));
    tree->SetBranchAddress(fgCenterY.name, std::addressof(fgCenterY.value));
    tree->SetBranchAddress(fgRadius.name, std::addressof(fgRadius.value));
    tree->SetBranchAddress(fgZ0.name, std::addressof(fgZ0.value));
    tree->SetBranchAddress(fgAlpha.name, std::addressof(fgAlpha.value));
}
