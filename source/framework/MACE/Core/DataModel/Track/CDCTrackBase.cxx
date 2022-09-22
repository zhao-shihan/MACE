#include "MACE/Core/DataModel/Track/CDCTrackBase.hxx"

namespace MACE::Core::DataModel::Track {

BranchSocket::IntBranchSocket CDCTrackBase::fgNumHits("numHits", 0);
BranchSocket::FloatBranchSocket CDCTrackBase::fgChi2("chi2", 0);
BranchSocket::DoubleBranchSocket CDCTrackBase::fgVertexTime("vtxTime", 0);

CDCTrackBase::CDCTrackBase() noexcept :
    fNumHits(fgNumHits.Value()),
    fChi2(fgChi2.Value()),
    fVertexTime(fgVertexTime.Value()) {}

void CDCTrackBase::FillBranchSockets() const noexcept {
    fgNumHits.Value(fNumHits);
    fgChi2.Value(fChi2);
    fgVertexTime.Value(fVertexTime);
}

void CDCTrackBase::CreateBranches(TTree& tree) {
    fgNumHits.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
}

void CDCTrackBase::ConnectToBranches(TTree& tree) {
    fgNumHits.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Track
