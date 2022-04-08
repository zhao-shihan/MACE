#include "MACE/Core/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

ShortStringBranchSocket EMCalSimHit::fgParticle("particle", "");
IntBranchSocket EMCalSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket EMCalSimHit::fgG4TrackID("g4TrackID", -1);

EMCalSimHit::EMCalSimHit() noexcept :
    EMCalHit(),
    fParticle(fgParticle.GetValue()),
    fG4EventID(fgG4EventID.GetValue()),
    fG4TrackID(fgG4TrackID.GetValue()) {}

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
    fgParticle.SetValue(fParticle);
    fgG4EventID.SetValue(fG4EventID);
    fgG4TrackID.SetValue(fG4TrackID);
}

} // namespace MACE::Core::DataModel::SimHit
