#include "MACE/Core/DataModel/SimTrack/ICDCSimTrack.hxx"

namespace MACE::Core::DataModel::Track {

IntBranchSocket ICDCSimTrack::fgTrueNumHits("trueNumHits", 0);
DoubleBranchSocket ICDCSimTrack::fgTrueVertexTime("trueVtxTime", 0);

ICDCSimTrack::ICDCSimTrack() noexcept :
    ITransientData(),
    fTrueNumHits(fgTrueNumHits.GetValue()),
    fTrueVertexTime(fgTrueVertexTime.GetValue()) {}

ICDCSimTrack::~ICDCSimTrack() noexcept = default;

void ICDCSimTrack::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgTrueNumHits.CreateBranch(tree);
    fgTrueVertexTime.CreateBranch(tree);
}

void ICDCSimTrack::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgTrueNumHits.ConnectToBranch(tree);
    fgTrueVertexTime.ConnectToBranch(tree);
}

void ICDCSimTrack::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgTrueNumHits.SetValue(fTrueNumHits);
    fgTrueVertexTime.SetValue(fTrueVertexTime);
}

} // namespace MACE::Core::DataModel::Track
