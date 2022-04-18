#include "MACE/Simulation/SimTarget/MuoniumTrack.hxx"

namespace MACE::Simulation::SimTarget {

DoubleBranchSocket MuoniumTrack::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket MuoniumTrack::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
DoubleBranchSocket MuoniumTrack::fgDecayTime("dcyTime", 0);
Vector3FBranchSocket MuoniumTrack::fgDecayPosition("dcyPos", {"x", "y", "z"}, {0, 0, 0});

MuoniumTrack::MuoniumTrack() noexcept :
    ITransientData(),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue<double>()),
    fDecayTime(fgDecayTime.GetValue()),
    fDecayPosition(fgDecayPosition.GetValue<double>()) {}

void MuoniumTrack::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgDecayTime.CreateBranch(tree);
    fgDecayPosition.CreateBranch(tree);
}

void MuoniumTrack::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgDecayTime.ConnectToBranch(tree);
    fgDecayPosition.ConnectToBranch(tree);
}

void MuoniumTrack::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgDecayTime.SetValue(fDecayTime);
    fgDecayPosition.SetValue(fDecayPosition);
}

} // namespace MACE::Simulation::SimTarget
