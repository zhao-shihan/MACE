#include "MACE/Core/DataModel/Track/ICDCTrack.hxx"

namespace MACE::Core::DataModel::Track {

IntBranchSocket ICDCTrack::fgNumHits("numHits", 0);
FloatBranchSocket ICDCTrack::fgChi2("chi2", 0);
DoubleBranchSocket ICDCTrack::fgVertexTime("vtxTime", 0);

ICDCTrack::ICDCTrack() noexcept :
    fNumHits(fgNumHits.Value()),
    fChi2(fgChi2.Value()),
    fVertexTime(fgVertexTime.Value()) {}

ICDCTrack::~ICDCTrack() noexcept = default;

void ICDCTrack::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgNumHits.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
}

void ICDCTrack::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgNumHits.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
}

void ICDCTrack::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgNumHits.Value(fNumHits);
    fgChi2.Value(fChi2);
    fgVertexTime.Value(fVertexTime);
}

} // namespace MACE::Core::DataModel::Track
