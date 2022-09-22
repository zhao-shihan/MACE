#include "MACE/Core/DataModel/Hit/EMCalHit.hxx"

namespace MACE::Core::DataModel::Hit {

BranchSocket::DoubleBranchSocket EMCalHit::fgHitTime("hitTime", 0);
BranchSocket::FloatBranchSocket EMCalHit::fgEnergy("hitEne", 0);
BranchSocket::FloatBranchSocket EMCalHit::fgEnergyVariance("hitEneVar", 0);

EMCalHit::EMCalHit() noexcept :
    fHitTime(fgHitTime.Value()),
    fEnergy(fgEnergy.Value()),
    fEnergyVariance(fgEnergyVariance.Value()) {}

void EMCalHit::FillBranchSockets() const noexcept {
    fgHitTime.Value(fHitTime);
    fgEnergy.Value(fEnergy);
    fgEnergyVariance.Value(fEnergyVariance);
}

void EMCalHit::CreateBranches(TTree& tree) {
    fgHitTime.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
    fgEnergyVariance.CreateBranch(tree);
}

void EMCalHit::ConnectToBranches(TTree& tree) {
    fgHitTime.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
    fgEnergyVariance.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Hit
