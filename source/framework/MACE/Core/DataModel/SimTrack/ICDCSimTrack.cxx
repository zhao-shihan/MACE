#include "MACE/Core/DataModel/SimTrack/ICDCSimTrack.hxx"

namespace MACE::Core::DataModel::Track {

IntBranchSocket ICDCSimTrack::fgTrueNumHits("trueNumHits", 0);
DoubleBranchSocket ICDCSimTrack::fgTrueVertexTime("trueVtxTime", 0);

ICDCSimTrack::ICDCSimTrack() noexcept :
    fTrueNumHits(fgTrueNumHits.Value()),
    fTrueVertexTime(fgTrueVertexTime.Value()) {}

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
    fgTrueNumHits.Value(fTrueNumHits);
    fgTrueVertexTime.Value(fTrueVertexTime);
}

} // namespace MACE::Core::DataModel::Track
