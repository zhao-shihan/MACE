#include "MACE/Core/DataModel/Track/ICDCTrack.hxx"

namespace MACE::Core::DataModel::Track {

IntBranchSocket ICDCTrack::fgNumHits("numHits", 0);
FloatBranchSocket ICDCTrack::fgChi2("chi2", 0);
DoubleBranchSocket ICDCTrack::fgVertexTime("vtxTime", 0);

ICDCTrack::ICDCTrack() noexcept :
    ITransientData(),
    fNumHits(fgNumHits.GetValue()),
    fChi2(fgChi2.GetValue()),
    fVertexTime(fgVertexTime.GetValue()) {}

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
    fgNumHits.SetValue(fNumHits);
    fgChi2.SetValue(fChi2);
    fgVertexTime.SetValue(fVertexTime);
}

} // namespace MACE::Core::DataModel::Track
