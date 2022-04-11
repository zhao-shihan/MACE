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
    fVertexTime.CreateBranch(tree);
    fVertexPosition.CreateBranch(tree);
    fDecayTime.CreateBranch(tree);
    fDecayPosition.CreateBranch(tree);
}

void MuoniumTrack::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fVertexTime.ConnectToBranches(tree);
    fVertexPosition.ConnectToBranches(tree);
    fDecayTime.ConnectToBranches(tree);
    fDecayPosition.ConnectToBranches(tree);
}

void MuoniumTrack::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgDecayTime.SetValue(fDecayTime);
    fgDecayPosition.SetValue(fDecayPosition);
}

} // namespace MACE::Simulation::SimTarget
