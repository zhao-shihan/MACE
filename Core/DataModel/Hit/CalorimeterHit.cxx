#include "Core/DataModel/Hit/CalorimeterHit.hxx"

namespace MACE::Core::DataModel::Hit {

DoubleBranchSocket CalorimeterHit::fgHitTime("hitTime", 0);
FloatBranchSocket CalorimeterHit::fgEnergy("hitEne", 0);
FloatBranchSocket CalorimeterHit::fgEnergyVariance("hitEneVar", 0);

CalorimeterHit::CalorimeterHit() noexcept :
    ITransientData(),
    fHitTime(fgHitTime.GetValue()),
    fEnergy(fgEnergy.GetValue()),
    fEnergyVariance(fgEnergyVariance.GetValue()) {}

void CalorimeterHit::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
    fgEnergyVariance.CreateBranch(tree);
}

void CalorimeterHit::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
    fgEnergyVariance.ConnectToBranch(tree);
}

 void CalorimeterHit::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgHitTime.SetValue(fHitTime);
    fgEnergy.SetValue(fEnergy);
    fgEnergyVariance.SetValue(fEnergyVariance);
}

} // namespace MACE::Core::DataModel::Hit
