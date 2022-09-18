#include "MACE/Core/DataModel/Hit/EMCalHit.hxx"

namespace MACE::Core::DataModel::Hit {

DoubleBranchSocket EMCalHit::fgHitTime("hitTime", 0);
FloatBranchSocket EMCalHit::fgEnergy("hitEne", 0);
FloatBranchSocket EMCalHit::fgEnergyVariance("hitEneVar", 0);

EMCalHit::EMCalHit() noexcept :
    ITransientData(),
    fHitTime(fgHitTime.Value()),
    fEnergy(fgEnergy.Value()),
    fEnergyVariance(fgEnergyVariance.Value()) {}

void EMCalHit::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
    fgEnergyVariance.CreateBranch(tree);
}

void EMCalHit::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
    fgEnergyVariance.ConnectToBranch(tree);
}

void EMCalHit::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgHitTime.Value(fHitTime);
    fgEnergy.Value(fEnergy);
    fgEnergyVariance.Value(fEnergyVariance);
}

} // namespace MACE::Core::DataModel::Hit
