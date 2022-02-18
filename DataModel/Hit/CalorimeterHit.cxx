#include "DataModel/Hit/CalorimeterHit.hxx"

using namespace MACE::DataModel;

Column<Float_t> CalorimeterHit::fgHitTime = { "HitT", 0.0f };
Column<Float_t> CalorimeterHit::fgEnergy = { "Energy", 0.0f };

CalorimeterHit::CalorimeterHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fEnergy(fgEnergy.value) {}

void CalorimeterHit::CreateBranches(TTree& tree) {
    Data::CreateBranches(tree);
    tree.Branch(fgHitTime.name, std::addressof(fgHitTime.value));
    tree.Branch(fgEnergy.name, std::addressof(fgEnergy.value));
}

void CalorimeterHit::ReadBranches(TTree& tree) {
    Data::ReadBranches(tree);
    tree.SetBranchAddress(fgHitTime.name, std::addressof(fgHitTime.value));
    tree.SetBranchAddress(fgEnergy.name, std::addressof(fgHitTime.value));
}
