#include "MACE/Core/DataModel/Track/MuoniumTrack.hxx"

namespace MACE::Core::DataModel::Track {

BranchSocket::DoubleBranchSocket MuoniumTrack::fgVertexTime("vtxTime", 0);
BranchSocket::Vector3FBranchSocket MuoniumTrack::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::Vector3FBranchSocket MuoniumTrack::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::DoubleBranchSocket MuoniumTrack::fgDecayTime("dcyTime", 0);
BranchSocket::Vector3FBranchSocket MuoniumTrack::fgDecayPosition("dcyPos", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::Vector3FBranchSocket MuoniumTrack::fgDecayMomentum("dcyMom", {"x", "y", "z"}, {0, 0, 0});

MuoniumTrack::MuoniumTrack() noexcept :
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value<double>()),
    fVertexMomentum(fgVertexMomentum.Value<double>()),
    fDecayTime(fgDecayTime.Value()),
    fDecayPosition(fgDecayPosition.Value<double>()),
    fDecayMomentum(fgVertexMomentum.Value<double>()) {}

void MuoniumTrack::FillBranchSockets() const noexcept {
    fgVertexTime.Value(fVertexTime);
    fgVertexPosition.Value(fVertexPosition);
    fgVertexMomentum.Value(fVertexMomentum);
    fgDecayTime.Value(fDecayTime);
    fgDecayPosition.Value(fDecayPosition);
    fgDecayMomentum.Value(fDecayMomentum);
}

void MuoniumTrack::CreateBranches(TTree& tree) {
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgDecayTime.CreateBranch(tree);
    fgDecayPosition.CreateBranch(tree);
    fgDecayMomentum.CreateBranch(tree);
}

void MuoniumTrack::ConnectToBranches(TTree& tree) {
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgDecayTime.ConnectToBranch(tree);
    fgDecayPosition.ConnectToBranch(tree);
    fgDecayMomentum.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::SimTrack
