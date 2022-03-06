#include "DataModel/Hit/CalorimeterHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket        CalorimeterHit::fgHitTime("hitT", 0.0);
FloatBranchSocket         CalorimeterHit::fgEnergy("E", 0.0);
FloatBranchSocket CalorimeterHit::fgEnergyVariance("varE", 0.0);

CalorimeterHit::CalorimeterHit() noexcept :
    Base(),
    fHitTime(fgHitTime.Value()),
    fEnergy(fgEnergy.Value()),
    fEnergyVariance(fgEnergyVariance.Value()) {}

void CalorimeterHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    tree.Branch(fgHitTime.BranchName(), fgHitTime.Address());
    tree.Branch(fgEnergy.BranchName(), fgEnergy.Address());
    tree.Branch(fgEnergyVariance.BranchName(), fgEnergyVariance.Address());
}

void CalorimeterHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgHitTime.BranchName(), fgHitTime.Address());
    tree.SetBranchAddress(fgEnergy.BranchName(), fgEnergy.Address());
    tree.SetBranchAddress(fgEnergyVariance.BranchName(), fgEnergyVariance.Address());
}
