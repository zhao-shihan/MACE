#include "DataModel/Hit/CalorimeterHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket        CalorimeterHit::fgHitTime("HitT", 0.0);
FloatBranchSocket         CalorimeterHit::fgEnergy("Energy", 0.0);
FloatBranchSocket CalorimeterHit::fgEnergyVariance("EnergyVar", 0.0);

CalorimeterHit::CalorimeterHit() noexcept :
    Data(),
    fHitTime(fgHitTime.Value()),
    fEnergy(fgEnergy.Value()),
    fEnergyVariance(fgEnergyVariance.Value()) {}

void CalorimeterHit::CreateBranches(TTree& tree) {
    Data::CreateBranches(tree);
    tree.Branch(fgHitTime.BranchName(), fgHitTime.Address());
    tree.Branch(fgEnergy.BranchName(), fgEnergy.Address());
    tree.Branch(fgEnergyVariance.BranchName(), fgEnergyVariance.Address());
}

void CalorimeterHit::ReadBranches(TTree& tree) {
    Data::ReadBranches(tree);
    tree.SetBranchAddress(fgHitTime.BranchName(), fgHitTime.Address());
    tree.SetBranchAddress(fgEnergy.BranchName(), fgEnergy.Address());
    tree.SetBranchAddress(fgEnergyVariance.BranchName(), fgEnergyVariance.Address());
}
