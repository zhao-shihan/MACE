#include "Core/DataModel/SimHit/CalorimeterSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

ShortStringBranchSocket CalorimeterSimHit::fgParticle("particle", "");
IntBranchSocket CalorimeterSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket CalorimeterSimHit::fgG4TrackID("g4TrackID", -1);

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    CalorimeterHit(),
    fParticle(fgParticle.GetValue()),
    fG4EventID(fgG4EventID.GetValue()),
    fG4TrackID(fgG4TrackID.GetValue()) {}

void CalorimeterSimHit::CreateBranches(TTree& tree) {
    CalorimeterHit::CreateBranches(tree);
    fgParticle.CreateBranch(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
}

void CalorimeterSimHit::ConnectToBranches(TTree& tree) {
    CalorimeterHit::ConnectToBranches(tree);
    fgParticle.ConnectToBranch(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
}

void CalorimeterSimHit::FillBranchSockets() const noexcept {
    CalorimeterHit::FillBranchSockets();
    fgParticle.SetValue(fParticle);
    fgG4EventID.SetValue(fG4EventID);
    fgG4TrackID.SetValue(fG4TrackID);
}

} // namespace MACE::Core::DataModel::SimHit
