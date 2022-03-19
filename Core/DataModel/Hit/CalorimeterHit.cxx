#include "DataModel/Hit/CalorimeterHit.hxx"

using namespace MACE::DataModel;

DoubleBranchSocket       CalorimeterHit::fgHitTime("hitTime", 0);
FloatBranchSocket         CalorimeterHit::fgEnergy("hitEne", 0);
FloatBranchSocket CalorimeterHit::fgEnergyVariance("hitEneVar", 0);

CalorimeterHit::CalorimeterHit() noexcept :
    Base(),
    fHitTime(fgHitTime.GetValue()),
    fEnergy(fgEnergy.GetValue()),
    fEnergyVariance(fgEnergyVariance.GetValue()) {}

void CalorimeterHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
    fgEnergyVariance.CreateBranch(tree);
}

void CalorimeterHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
    fgEnergyVariance.ConnectToBranch(tree);
}
