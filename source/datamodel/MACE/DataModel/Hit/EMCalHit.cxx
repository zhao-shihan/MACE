#include "MACE/DataModel/Hit/EMCalHit.hxx"

namespace MACE::DataModel {

template<>
EMCalHit::Field::Time::BranchSocket EMCalHit::Field::Time::Base::fgBranchSocket = 
    {"t", "Hitting Time", 0};
template<>
EMCalHit::Field::EnergyDeposition::BranchSocket EMCalHit::Field::EnergyDeposition::Base::fgBranchSocket = 
    {"E", "Energy Deposition", 0};

inline namespace Hit {

void EMCalHit::CreateAllBranch(TTree& tree) {
    Field::Time::CreateBranch(tree);
    Field::EnergyDeposition::CreateBranch(tree);
}

void EMCalHit::ConnectToAllBranch(TTree& tree) {
    Field::Time::ConnectToBranch(tree);
    Field::EnergyDeposition::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
