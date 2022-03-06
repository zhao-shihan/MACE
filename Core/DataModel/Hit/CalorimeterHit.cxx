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
