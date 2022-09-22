#include "MACE/Core/DataModel/SimTrack/CDCSimTrackBase.hxx"

namespace MACE::Core::DataModel::Track {

BranchSocket::IntBranchSocket CDCSimTrackBase::fgTrueNumHits("trueNumHits", 0);
BranchSocket::DoubleBranchSocket CDCSimTrackBase::fgTrueVertexTime("trueVtxTime", 0);

CDCSimTrackBase::CDCSimTrackBase() noexcept :
    fTrueNumHits(fgTrueNumHits.Value()),
    fTrueVertexTime(fgTrueVertexTime.Value()) {}

void CDCSimTrackBase::FillBranchSockets() const noexcept {
    fgTrueNumHits.Value(fTrueNumHits);
    fgTrueVertexTime.Value(fTrueVertexTime);
}

void CDCSimTrackBase::CreateBranches(TTree& tree) {
    fgTrueNumHits.CreateBranch(tree);
    fgTrueVertexTime.CreateBranch(tree);
}

void CDCSimTrackBase::ConnectToBranches(TTree& tree) {
    fgTrueNumHits.ConnectToBranch(tree);
    fgTrueVertexTime.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Track
