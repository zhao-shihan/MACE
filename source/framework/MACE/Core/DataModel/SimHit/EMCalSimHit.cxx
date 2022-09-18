#include "MACE/Core/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

ShortStringBranchSocket EMCalSimHit::fgParticle("particle", "");
IntBranchSocket EMCalSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket EMCalSimHit::fgG4TrackID("g4TrackID", -1);

EMCalSimHit::EMCalSimHit() noexcept :
    EMCalHit(),
    fParticle(fgParticle.Value()),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()) {}

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

void EMCalSimHit::FillBranchSockets() const noexcept {
    EMCalHit::FillBranchSockets();
    fgParticle.Value(fParticle);
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
}

} // namespace MACE::Core::DataModel::SimHit
