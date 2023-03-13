#include "MACE/DataModel/SimTrack/MuoniumSimTrack.hxx"

namespace MACE::DataModel::SimTrack {

BranchSocket::ShortStringBranchSocket MuoniumSimTrack::fgParticle("particle", "");
BranchSocket::IntBranchSocket MuoniumSimTrack::fgG4EventID("g4EventID", -1);
BranchSocket::IntBranchSocket MuoniumSimTrack::fgG4TrackID("g4TrackID", -1);

MuoniumSimTrack::MuoniumSimTrack() noexcept :
    MuoniumTrack(),
    fParticle(fgParticle.Value()),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()) {}

void MuoniumSimTrack::FillBranchSockets() const noexcept {
    MuoniumTrack::FillBranchSockets();
    fgParticle.Value(fParticle);
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
}

void MuoniumSimTrack::CreateBranches(TTree& tree) {
    MuoniumTrack::CreateBranches(tree);
    fgParticle.CreateBranch(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
}

void MuoniumSimTrack::ConnectToBranches(TTree& tree) {
    MuoniumTrack::ConnectToBranches(tree);
    fgParticle.ConnectToBranch(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
}

} // namespace MACE::DataModel::SimTrack
