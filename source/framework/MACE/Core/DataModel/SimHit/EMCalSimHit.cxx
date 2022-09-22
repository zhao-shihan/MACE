#include "MACE/Core/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

BranchSocket::ShortStringBranchSocket EMCalSimHit::fgParticle("particle", "");
BranchSocket::IntBranchSocket EMCalSimHit::fgG4EventID("g4EventID", -1);
BranchSocket::IntBranchSocket EMCalSimHit::fgG4TrackID("g4TrackID", -1);

EMCalSimHit::EMCalSimHit() noexcept :
    EMCalHit(),
    fParticle(fgParticle.Value()),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()) {}

void EMCalSimHit::FillBranchSockets() const noexcept {
    EMCalHit::FillBranchSockets();
    fgParticle.Value(fParticle);
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
}

void EMCalSimHit::CreateBranches(TTree& tree) {
    EMCalHit::CreateBranches(tree);
    fgParticle.CreateBranch(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
}

void EMCalSimHit::ConnectToBranches(TTree& tree) {
    EMCalHit::ConnectToBranches(tree);
    fgParticle.ConnectToBranch(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::SimHit
